#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Car.h"
#include "Player.h"
#include "Obstacle.h"
#include "Images.h" 
#include "Enums.h"
#include "Sort.h"
#include "Sounds.h"

Arduboy2 arduboy; 
ArduboyTones sound(arduboy.audio.on);

#define CAR_LAUNCH_DELAY_MAX          120
#define CAR_LAUNCH_DELAY_MIN          60

#define OBSTACLE_LAUNCH_DELAY_MAX     400
#define OBSTACLE_LAUNCH_DELAY_MIN     200

#define ROADSIDE_LAUNCH_DELAY_MAX     50
#define ROADSIDE_LAUNCH_DELAY_MIN     25

#define NUMBER_OF_CAR_IMAGES          8
#define NUMBER_OF_CARS                3
#define NUMBER_OF_OBSTACLES           3
#define NUMBER_OF_ROADSIDES           6
#define ROAD_IMAGES_HEIGHT            24

#define ROAD_OFFSET_UPPER             22
#define ROAD_OFFSET_LOWER             2
#define ROAD_Y_MIN                    -18 
#define ROAD_Y_MAX                    -6 

RoadElement roadElements[17];
Road road = { 0, -16, 64, RoadType::Straight, 0, 2 };
Player player = {20, 24, car_player, mask_player};

const byte *car_images[] = { car_01, car_02, car_03, car_04, car_05, car_06, car_07, car_08 };
const byte *car_masks[] =  { mask_01, mask_02, mask_03, mask_04, mask_05, mask_06, mask_07, mask_08 };
const byte *obstacle_images[] = { roughPatch, crossing };
const byte *obstacle_masks[] = { roughPatch, crossing };
const byte *roadside_images[] = { tree, bush };
const byte *roadside_masks[] = { mask_tree, mask_bush };
const byte *upper_road_images[] = { upper_road, upper_road_up, upper_road_down, upper_road_fadeout, upper_road_fadein };
const byte *lower_road_images[] = { lower_road, lower_road_up, lower_road_down, lower_road_fadeout, lower_road_fadein };

Car cars[3] = {
  {1, -80, 0, 0, car_images[2], car_masks[2], cars, SteeringType::ZigZag},
  {2, -80, 0, 0, car_images[3], car_masks[3], cars, SteeringType::ZigZag},
  {3, -80, 0, 0, car_images[4], car_masks[4], cars, SteeringType::ZigZag}
};

Obstacle obstacles[3] = {
  {-20, 24, obstacle_images[0], obstacle_masks[0]},
  {-20, 24, obstacle_images[0], obstacle_masks[0]},
  {-20, 24, obstacle_images[0], obstacle_masks[0]}
};

Obstacle roadsides[6] = {
  {-20, 24, roadside_images[0], roadside_masks[0]},
  {-20, 24, roadside_images[0], roadside_masks[0]},
  {-20, 24, roadside_images[0], roadside_masks[0]},
  {-20, 24, roadside_images[0], roadside_masks[0]},
  {-20, 24, roadside_images[0], roadside_masks[0]},
  {-20, 24, roadside_images[0], roadside_masks[0]}
};


const uint8_t scrollIncrement = 2;
const uint8_t frame = 0;

int16_t idx = 0; // scratch variable.

uint16_t carLaunchCountdown = CAR_LAUNCH_DELAY_MIN;
uint16_t carLaunchDelay = CAR_LAUNCH_DELAY_MIN;  // Stores the carLaunchCountdown when launching a new car, the bigger the number. the faster the car can go.
uint16_t obstacleLaunchCountdown = OBSTACLE_LAUNCH_DELAY_MIN;
uint16_t roadsideLaunchCountdown = ROADSIDE_LAUNCH_DELAY_MIN;


bool sortByNewX(Car x, Car y) {
  
  if (x.getNewX() > y.getNewX()) {
    return true;
  } 
  else {
    return false;
  }
  
}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Setup
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void setup() {
  
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();

  for (idx = 0; idx < 17; ++idx) {

    roadElements[idx].upperLimit = -16;
    roadElements[idx].lowerLimit = road.height + -16;
    roadElements[idx].roadType = RoadType::Straight;
    
  }

  arduboy.clear();
  arduboy.fillRect(0, 0, WIDTH, HEIGHT, WHITE);
  Sprites::drawOverwrite(0, 0, Hannibal, frame);
  arduboy.display();

  while (!arduboy.pressed(A_BUTTON)) {
    delay(100);
  }
  
  arduboy.clear();

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Let's play !
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void loop() {

  if (!(arduboy.nextFrame())) return;

  
  // Clear the screen ..

  player.clearImage(frame);

  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {
    cars[idx].clearImage(frame);
  }

  for (idx = 0; idx < NUMBER_OF_OBSTACLES; ++idx) {
    obstacles[idx].clearImage(frame);
  }

  for (idx = 0; idx < NUMBER_OF_ROADSIDES; ++idx) {
    roadsides[idx].clearImage(frame);
  }


  // Handle player movement ..
  
  if (arduboy.pressed(UP_BUTTON) && player.getY() > 0)                                { player.setNewY(player.getY() - static_cast<SQ7x8>(0.5)); }
  if (arduboy.pressed(DOWN_BUTTON) && player.getY() < HEIGHT - player.getHeight())    { player.setNewY(player.getY() + static_cast<SQ7x8>(0.5)); }
  if (arduboy.pressed(LEFT_BUTTON) && player.getX() > 0)                              { player.setNewX(player.getX() - static_cast<SQ7x8>(0.75)); }
  if (arduboy.pressed(RIGHT_BUTTON) && player.getX() < 64)                            { player.setNewX(player.getX() + static_cast<SQ7x8>(1.00)); }



  // Is the player in the rough ?

  if (player.getY().GetInteger() < getRoadElement_UpperLimit(player.getX()) + ROAD_OFFSET_UPPER)                         { sound.tones(sound_drivingInRough); player.setNewX(player.getX() - static_cast<SQ7x8>(0.4)); }
  if (player.getY().GetInteger() + player.getHeight() > getRoadElement_LowerLimit(player.getX()) + ROAD_OFFSET_LOWER)    { sound.tones(sound_drivingInRough); player.setNewX(player.getX() - static_cast<SQ7x8>(0.4)); }



  // Should we launch another car?
  
  --carLaunchCountdown;
  
  if (carLaunchCountdown == 0) {

    for (uint8_t carNumber = 0; carNumber < NUMBER_OF_CARS; ++carNumber) {

      if (!cars[carNumber].getEnabled()) { 
        launchCar(carNumber, carLaunchDelay); 
        break;
      }

    }

    carLaunchCountdown = random(CAR_LAUNCH_DELAY_MIN, CAR_LAUNCH_DELAY_MAX);
    carLaunchDelay = carLaunchCountdown;
            
  }



  // Should we launch another obstacle?
  
  --obstacleLaunchCountdown;
  
  if (obstacleLaunchCountdown == 0) {

    for (uint8_t obstacleNumber = 0; obstacleNumber < NUMBER_OF_OBSTACLES; ++obstacleNumber) {

      if (!obstacles[obstacleNumber].getEnabled()) { 
        launchObstacle(obstacleNumber); 
        break;
      }

    }

    obstacleLaunchCountdown = random(OBSTACLE_LAUNCH_DELAY_MIN, OBSTACLE_LAUNCH_DELAY_MAX);
            
  }



  // Should we launch another roadside item?  Only if we have enough roadside to render it against.

  if (road.y == ROAD_Y_MIN || road.y == ROAD_Y_MAX) { 

    --roadsideLaunchCountdown;
    
    if (roadsideLaunchCountdown == 0) {

      for (uint8_t roadsideNumber = 0; roadsideNumber < NUMBER_OF_ROADSIDES; ++roadsideNumber) {
  
        if (!roadsides[roadsideNumber].getEnabled()) { 
          launchRoadside(roadsideNumber, (road.y == ROAD_Y_MIN)); 
          break;
        }
  
      }
  
      roadsideLaunchCountdown = random(ROADSIDE_LAUNCH_DELAY_MIN, ROADSIDE_LAUNCH_DELAY_MAX);
              
    }

  }



  // Update the position of the obstacles .. (they don't move).
  
  for (idx = 0; idx < NUMBER_OF_OBSTACLES; ++idx) {
    if (obstacles[idx].getEnabled()) { 
      obstacles[idx].move(scrollIncrement); 
    }
  }
  


  // Update the position of the roadside things .. (they don't move).
  
  for (idx = 0; idx < NUMBER_OF_ROADSIDES; ++idx) {
    if (roadsides[idx].getEnabled()) { 
      roadsides[idx].move(scrollIncrement); 
    }
  }


  // Calculate the new positions of the car based on their movement type ..

  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {
    if (cars[idx].getEnabled()) { 
      cars[idx].calcNewPosition(scrollIncrement, getRoadElement_UpperLimit(cars[idx].getX()) + ROAD_OFFSET_UPPER, getRoadElement_LowerLimit(cars[idx].getX()) + ROAD_OFFSET_LOWER); 
    }
  }



  // Is the player touching any other cars?

  bool collisionAlreadyDetected = false;

  for (idx = 0; idx < 3; ++idx) {

    if (arduboy.collide(player.getNewRect(), cars[idx].getNewRect())) {


      // Only move the car back once - even if it is touching multiple cars ..
      
      if (!collisionAlreadyDetected) { 
        player.setNewX(player.getX() - static_cast<SQ7x8>(0.4));
        sound.tones(sound_bump); 
        collisionAlreadyDetected = true;
      }

      cars[idx].setNewX(cars[idx].getX() + static_cast<SQ7x8>(0.4));
      
    }
    
  }


  // Are any cars touching other cars ?  Sort the cars into order so that the left most is processed first ..

  sortArray(cars, 3, sortByNewX);

  bool checkCars = true;

  while (checkCars) {  
    
    checkCars = false;

    for (uint8_t left = 0; left < 3; ++left) {
      
      if (cars[left].getEnabled()) {
    
        for (uint8_t right = left + 1; right < 3; ++right) {
      
          if (cars[right].getEnabled()) {
   
           if (arduboy.collide( cars[left].getNewRect(), cars[right].getNewRect() )) {
              
//              Serial.print("Car "); Serial.print(left); Serial.print(" and "); Serial.print(right); Serial.print(" have collided. ");
//              for (uint8_t q = 0; q < 3; ++q) { 
//                Serial.print("{"); 
//                Serial.print(cars[q].getName()); 
//                Serial.print(":"); 
//                Serial.print(cars[q].getEnabled() ? "T": "F");  
//                Serial.print(":"); 
//                Serial.print(static_cast<float>(cars[q].getNewX())); 
//                Serial.print(":"); 
//                Serial.print(static_cast<float>(cars[q].getNewY())); 
//                Serial.print(":"); 
//                Serial.print(static_cast<float>(cars[q].getSpeedX())); 
//                Serial.print("} "); 
//              } 
//              Serial.println("");


              // We are about to move pne of the cars so this test will need to be done again ..

              checkCars = true;
              cars[right].setNewX(cars[right].getNewX() + 2);
  

              // Check to see if the new placement of the car is still causing a collision. If 
              // so bump the car up or down depending on which way the car has moved already ..
              
              if (arduboy.collide( cars[left].getNewRect(), cars[right].getNewRect() )) {

//                Serial.print("Move from "); 
//                Serial.print(static_cast<float>(cars[right].getY())); 
//                Serial.print(" to "); 
//                Serial.print(static_cast<float>(cars[right].getNewY())); 
//                Serial.print(" = "); 
//                Serial.print(static_cast<float>(cars[right].getDeltaY()));
                
                if (cars[right].getDeltaY() < 0) { 
//                  Serial.println(" moving down");                  
                  cars[right].setNewX(cars[right].getNewX() + 1); 
                }
                else if (cars[right].getDeltaY() > 0) { 
//                  Serial.println(" moving up");                  
                  cars[right].setNewX(cars[right].getNewX() - 1); 
                }

              }

            }
  
          }
  
        }
    
      }
  
    }
    
  }


  // Update the position of the player and the cars ..
  
  player.updatePosition();
  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {
    if (cars[idx].getEnabled()) { cars[idx].updatePosition(); }
  }

  
  drawRoad();

  for (idx = 0; idx < NUMBER_OF_ROADSIDES; ++idx) {
    roadsides[idx].renderImage(frame);
  }
  
  for (idx = 0; idx < NUMBER_OF_OBSTACLES; ++idx) {
    obstacles[idx].renderImage(frame);
  }
  
  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {
    cars[idx].renderImage(frame);
  }

  player.renderImage(frame);

arduboy.fillRect(99,0,31,12, BLACK);
arduboy.drawRect(100,0,28,11, WHITE);
//arduboy.drawRect(108,2,5,6, WHITE);
Sprites::drawExternalMask(103, 2, littleCar, littleCar_Mask, frame, frame);
//Sprites::drawExternalMask(115, 2, littleCar, littleCar_Mask, frame, frame);
//  Sprites::drawExternalMask(103, 2, digit_0, digit_mask, frame, frame);
  Sprites::drawExternalMask(113, 2, digit_0, digit_mask, frame, frame);

  arduboy.display();
  delay(10);
  
  if (arduboy.pressed(A_BUTTON)) {
    delay(60);

    /* Debug car position */
    Serial.print("(player.getX().GetInteger() : ");
    Serial.print(player.getX().GetInteger());
    Serial.print(", getRoadElement_UpperLimit(player.getX().GetInteger()) + ROAD_OFFSET_UPPER : ");
    Serial.print(getRoadElement_UpperLimit(player.getX().GetInteger()) + ROAD_OFFSET_UPPER);
    Serial.print(", getRoadElement_LowerLimit(player.getX()) + ROAD_OFFSET_LOWER : ");
    Serial.println(getRoadElement_LowerLimit(player.getX().GetInteger()) + ROAD_OFFSET_LOWER);

  }
  if (arduboy.pressed(B_BUTTON)) {
    delay(250);
  }
  
}



/* -----------------------------------------------------------------------------------------------------------------------------
 *  Get the upper limit of the road at position X
 */
const int16_t getRoadElement_UpperLimit(SQ7x8 x) {

  return (x - road.x >= 0 ? roadElements[((x.GetInteger() - road.x) / 8)].upperLimit : roadElements[0].upperLimit);
  
}

/* -----------------------------------------------------------------------------------------------------------------------------
 *  Get the lower limit of the road at position X
 */
const int16_t getRoadElement_LowerLimit(SQ7x8 x) {

  return (x - road.x >= 0 ? roadElements[((x.GetInteger() - road.x) / 8)].lowerLimit : roadElements[0].lowerLimit);

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Launch a new car onto the road.
 * -----------------------------------------------------------------------------------------------------------------------------
 * 
 * SpeedX describes the horizontal movement of a car.  The larger this number, the faster the car and the SLOWER it moves 
 * from right to left.  
 * 
 * Logic: 
 * 
 * When launching a new car, the launchDelay indicates how long it has been since the last launch.  The larger the
 * delay, the slower we can make the new car go (and therefore it will move quickly from right to left) as there is 
 * theoretically a larger gap between this new car and the previous one.
 *   
 *   > 'launchDelay' is a value between CAR_LAUNCH_DELAY_MIN and CAR_LAUNCH_DELAY_MAX, assume values of 60 and 120.
 *   > If 'launchDelay' is 60 (smallest gap), then want the speed to be higher, in the range between (say) 100 - 160.
 *   > If 'launchDelay' is 80 (small gap), then want the speed to be higher, in the range between (say) 80 - 140.
 *   > If 'launchDelay' is 100 (large gap), then want the speed to be lower, in the range between (say) 60 - 120.
 *   > If 'launchDelay' is 120 (largest gap), then want the speed to be lower, in the range between (say) 40 - 100.
 *   
 *   .. or ..
 *   
 *                   launchDelay                                Speed Min                               Speed Max
 *   
 *   CAR_LAUNCH_DELAY_MIN =   60       LAUNCH_SPEED_X_LOW_RANGE_MAX = 100       LAUNCH_SPEED_X_HI_RANGE_MAX = 160
 *                            80                                       80                                     140
 *                           100                                       60                                     120
 *   CAR_LAUNCH_DELAY_MAX =  120       LAUNCH_SPEED_X_LOW_RANGE_MIN =  40       LAUNCH_SPEED_X_HI_RANGE_MIN = 100
 *   
 *   
 * Assume a launch delay of 80.  This is 1/3 of the way between CAR_LAUNCH_DELAY_MIN and CAR_LAUNCH_DELAY_MAX.  To calculate 
 * the range for the random number, I hacve used the following formulas:
 *  
 *   > ratio = (launchDelay - CAR_LAUNCH_DELAY_MIN) / (CAR_LAUNCH_DELAY_MAX - CAR_LAUNCH_DELAY_MIN)
 *   > minimum = ((1 - ratio) * (LAUNCH_SPEED_X_LOW_RANGE_MAX - LAUNCH_SPEED_X_LOW_RANGE_MIN)) + LAUNCH_SPEED_X_LOW_RANGE_MIN
 *   > maximum = LAUNCH_SPEED_X_HI_RANGE_MAX - ( ratio * (LAUNCH_SPEED_X_HI_RANGE_MAX - LAUNCH_SPEED_X_HI_RANGE_MIN))
 *       
 */
#define LAUNCH_SPEED_X_LOW_RANGE_MAX 100
#define LAUNCH_SPEED_X_LOW_RANGE_MIN 40
#define LAUNCH_SPEED_X_HI_RANGE_MAX 160
#define LAUNCH_SPEED_X_HI_RANGE_MIN 100
#define LAUNCH_SPEED_Y_MAX 20
#define LAUNCH_SPEED_Y_MIN 5
 
void launchCar(uint8_t carNumber, uint8_t launchDelay) {

  idx = random(0, NUMBER_OF_CAR_IMAGES);

  float ratio = (launchDelay - CAR_LAUNCH_DELAY_MIN) / (CAR_LAUNCH_DELAY_MAX - CAR_LAUNCH_DELAY_MIN);
  uint16_t speedXMin = ((1 - ratio) * (LAUNCH_SPEED_X_LOW_RANGE_MAX - LAUNCH_SPEED_X_LOW_RANGE_MIN)) + LAUNCH_SPEED_X_LOW_RANGE_MIN;
  uint16_t speedXMax = LAUNCH_SPEED_X_HI_RANGE_MAX - ( ratio * (LAUNCH_SPEED_X_HI_RANGE_MAX - LAUNCH_SPEED_X_HI_RANGE_MIN));
  
  cars[carNumber].setX(WIDTH);
  cars[carNumber].setEnabled(true);
  cars[carNumber].setBitmap(car_images[idx]); 
  cars[carNumber].setMask(car_masks[idx]); 
  cars[carNumber].setY(random(road.y  + ROAD_OFFSET_UPPER + 4 , road.y + road.height - 6 - cars[carNumber].getHeight()));
  cars[carNumber].setSpeedX((random(speedXMin, speedXMax) / 100.0)); 
  cars[carNumber].setSpeedY((random(LAUNCH_SPEED_Y_MIN, LAUNCH_SPEED_Y_MAX) / 100.0));
  cars[carNumber].setSteeringType(static_cast<SteeringType> (random((uint8_t)SteeringType::First, (uint8_t)SteeringType::Count)));

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Launch a new obstacle onto the road.
 * -----------------------------------------------------------------------------------------------------------------------------
 */
 void launchObstacle(uint8_t obstacleNumber) {

  idx = random(0, 2);
  
  switch (idx) {
    
    case 0:  // rough spot
      obstacles[obstacleNumber].setEnabled(true);
      obstacles[obstacleNumber].setX(WIDTH);
      obstacles[obstacleNumber].setY(random(road.y + ROAD_OFFSET_UPPER + 4 , road.y + road.height - 6 - obstacles[obstacleNumber].getHeight()));
      obstacles[obstacleNumber].setBitmap(obstacle_images[0]); 
      obstacles[obstacleNumber].setMask(obstacle_masks[0]); 
      break;
    
    case 1:  // crossing
      obstacles[obstacleNumber].setEnabled(true);
      obstacles[obstacleNumber].setX(WIDTH);
      obstacles[obstacleNumber].setY(road.y + ROAD_OFFSET_UPPER + 3);
      obstacles[obstacleNumber].setBitmap(obstacle_images[1]); 
      obstacles[obstacleNumber].setMask(obstacle_masks[1]); 
      break;

  }
  
 }


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Launch a new roadside image ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
 void launchRoadside(uint8_t roadsideNumber, bool top) {

  idx = random(0, 2);

  switch (idx) {
    
    case 0:  // rough spot
      roadsides[roadsideNumber].setEnabled(true);
      roadsides[roadsideNumber].setX(WIDTH);
      roadsides[roadsideNumber].setY(top ? 0 : 48);
      roadsides[roadsideNumber].setBitmap(roadside_images[0]); 
      roadsides[roadsideNumber].setMask(roadside_masks[0]); 
      break;
    
    case 1:  // rough spot
      roadsides[roadsideNumber].setEnabled(true);
      roadsides[roadsideNumber].setX(WIDTH);
      roadsides[roadsideNumber].setY(top ? 2 : 50);
      roadsides[roadsideNumber].setBitmap(roadside_images[1]); 
      roadsides[roadsideNumber].setMask(roadside_masks[1]); 
      break;
    
  }
  
 }

 
/* -----------------------------------------------------------------------------------------------------------------------------
 *  Draw road.
 * -----------------------------------------------------------------------------------------------------------------------------
 * 
 * The road is always a fixed width high.
 * The road is stored in 17 x 8 pixel wide images and they are rendered using a pixel offset in the road structure ..
 *       
 */
void drawRoad() {

  if (road.x == 6) {
      
    road.x = -scrollIncrement;
    road.type = RoadType::Straight;
    
    road.randomCount--;
    
    if (road.randomCount == 0) {
      
      if (road.randomNumber > 0) {
        road.randomNumber = 0;
      }
      else {
        road.randomNumber = random((uint8_t)RoadType::First, (uint8_t)RoadType::Count);   
      }

      road.randomCount = random(2, 6);
      
    }

    switch ((RoadType)road.randomNumber) {
      
      case RoadType::Straight:
        break;
        
      case RoadType::Up:
        if (road.y > -18) {
          road.y-=2;
          road.type = RoadType::Up;
        }
        break;
        
      case RoadType::Down:
        if (road.y < -6) {   // height = 64, -2 height = 72, -4 height = 68, -10
          road.y+=2;
          road.type = RoadType::Down;
        }
        break;
        
    }
   
    RoadElement * pt = roadElements;
    memmove(static_cast<void*>(&pt[0]), static_cast<const void*>(&pt[1]), 16 * sizeof(RoadElement));

    roadElements[16].upperLimit = road.y;
    roadElements[16].lowerLimit = road.y + road.height;
    roadElements[16].roadType = road.type;

  }

  road.x+=scrollIncrement;

//debugRoad();
  // Render the road.  
 
  for (idx = 0; idx < 17; ++idx) {
  
    int8_t upperLimitOffset = 0;
    int8_t lowerLimitOffset = 0;
  
    switch (roadElements[idx].roadType) {
      
      case RoadType::Straight:
        break;
       
      case RoadType::Up:
        upperLimitOffset = 2;
        break;
       
      case RoadType::Down:
        lowerLimitOffset = -2; 
        break;
        
    }
    
    Sprites::drawOverwrite((idx * 8) - road.x, roadElements[idx].upperLimit + upperLimitOffset, upper_road_images[((uint8_t)roadElements[idx].roadType)], frame);   
    Sprites::drawOverwrite((idx * 8) - road.x, roadElements[idx].lowerLimit + lowerLimitOffset, lower_road_images[((uint8_t)roadElements[idx].roadType)], frame);   

  }

}

void debugRoad() {
    Serial.print("2) ");
  for (int x = 0; x < 17; ++x) {
    Serial.print('{');
    Serial.print(roadElements[x].upperLimit);
    Serial.print(',');
    Serial.print(roadElements[x].lowerLimit);
    Serial.print(',');
    Serial.print((int)roadElements[x].roadType);
    Serial.print('}');
  }
  Serial.println(' ');

}

