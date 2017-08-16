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

#define NUMBER_OF_CAR_IMAGES          8
#define NUMBER_OF_CARS                3
#define NUMBER_OF_OBSTACLES           3
#define NUMBER_OF_OBSTACLES_INC_RAMP  NUMBER_OF_OBSTACLES + 2
#define NUMBER_OF_ROADSIDES           6
#define ROAD_IMAGES_HEIGHT            24

#define OBSTACLE_LAUNCH_DELAY_MAX     300
#define OBSTACLE_LAUNCH_DELAY_MIN     125
#define OBSTACLE_RAMP                 NUMBER_OF_OBSTACLES
#define OBSTACLE_CREVICE              OBSTACLE_RAMP + 1

#define ROAD_OFFSET_UPPER             22
#define ROAD_OFFSET_LOWER             2
#define ROAD_Y_MIN                    -18 
#define ROAD_Y_MAX                    -6 

#define FUEL_MAX                      16
#define FUEL_DECREMENT                0.010
#define FUEL_DECREMENT_BOOST          0.005

RoadElement roadElements[17];
Road road = { 0, -16, 64, RoadType::Straight, 0, 2 };
Player player = {20, 24, FUEL_MAX, car_player, mask_player};

const byte *car_images[] = { car_01, car_02, car_03, car_04, car_05, car_06, car_07, car_08 };
const byte *car_masks[] =  { mask_01, mask_02, mask_03, mask_04, mask_05, mask_06, mask_07, mask_08 };
const byte *obstacle_images[] = { roughPatch, crossing, fuel, jewel, ramp, crevice };
const byte *obstacle_masks[] = { roughPatch, crossing, fuel_mask, jewel_mask, ramp_mask, crevice_mask };
const byte *upper_road_images[] = { upper_road, upper_road_up, upper_road_down };
const byte *lower_road_images[] = { lower_road, lower_road_up, lower_road_down };

Car cars[3] = {
  {1, -80, 0, 0, car_images[2], car_masks[2], cars, SteeringType::ZigZag},
  {2, -80, 0, 0, car_images[3], car_masks[3], cars, SteeringType::ZigZag},
  {3, -80, 0, 0, car_images[4], car_masks[4], cars, SteeringType::ZigZag}
};

Obstacle obstacles[5] = {
  {-20, 24, obstacle_images[0], obstacle_masks[0]},
  {-20, 24, obstacle_images[0], obstacle_masks[0]},
  {-20, 24, obstacle_images[0], obstacle_masks[0]},
  {-20, 24, obstacle_images[0], obstacle_masks[0]},     // Reserved for the ramp.
  {-20, 24, obstacle_images[0], obstacle_masks[0]}      // Reserved for the crevice.
};


const uint8_t scrollIncrement = 2;
const uint8_t frame = 0;

int16_t idx = 0; // scratch variable.

uint16_t carLaunchCountdown = CAR_LAUNCH_DELAY_MIN;
uint16_t carLaunchDelay = CAR_LAUNCH_DELAY_MIN;  // Stores the carLaunchCountdown when launching a new car, the bigger the number. the faster the car can go.
uint16_t obstacleLaunchCountdown = OBSTACLE_LAUNCH_DELAY_MIN;


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
  Sprites::drawOverwrite(-6, -2, Hannibal, frame);
  arduboy.display();

  sound.tones(theme);
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

  for (idx = 0; idx < NUMBER_OF_OBSTACLES_INC_RAMP; ++idx) {
    obstacles[idx].clearImage(frame);
  }



  // Handle player movement ..
  
  player.setFuel(player.getFuel() - static_cast<SQ15x16>(FUEL_DECREMENT));
  
  if (arduboy.pressed(UP_BUTTON) && player.getY() > 0 && !collideWithCarAbove())                                { player.setY(player.getY() - static_cast<SQ15x16>(0.5)); }
  if (arduboy.pressed(DOWN_BUTTON) && player.getY() < HEIGHT - player.getHeight() && !collideWithCarBelow())    { player.setY(player.getY() + static_cast<SQ15x16>(0.5)); }
  if (arduboy.pressed(LEFT_BUTTON) && player.getX() > 0)                                                        { player.setX(player.getX() - static_cast<SQ15x16>(0.75)); }
  if (arduboy.pressed(RIGHT_BUTTON) && player.getX() < 64 && !collideWithCarInFront())                          { player.setFuel(player.getFuel() - static_cast<SQ15x16>(FUEL_DECREMENT_BOOST));
                                                                                                                  player.setX(player.getX() + static_cast<SQ15x16>(0.80)); }



  // Is the player in the rough ?

  if (player.getY().getInteger() < getRoadElement_UpperLimit(player.getX()) + ROAD_OFFSET_UPPER)                         { sound.tones(sound_drivingInRough); player.setX(player.getX() - static_cast<SQ15x16>(0.4)); }
  if (player.getY().getInteger() + player.getHeight() > getRoadElement_LowerLimit(player.getX()) + ROAD_OFFSET_LOWER)    { sound.tones(sound_drivingInRough); player.setX(player.getX() - static_cast<SQ15x16>(0.4)); }



  // Has the player hit an obstacle?

  for (idx = 0; idx < NUMBER_OF_OBSTACLES_INC_RAMP; ++idx) {
    
    if (obstacles[idx].getEnabled()) { 

      if (arduboy.collide(player.getNewRect(), obstacles[idx].getRect())) {

        switch (obstacles[idx].getObstacleType()) {

          case ObstacleType::RoughRoad:
            break;

          case ObstacleType::Crossing:
            break;

          case ObstacleType::Fuel:
            player.setFuel(FUEL_MAX);
            obstacles[idx].setEnabled(false);
            break;

          case ObstacleType::Jewel:
            player.setScore(player.getScore() + 1);
            obstacles[idx].setEnabled(false);
            break;

        }
        
      }

    }
    
  }



  // Should we launch another car?

  if (!obstacles[OBSTACLE_CREVICE].getEnabled()) {
    
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

  }



  // Should we launch another obstacle?
  
  if (!obstacles[OBSTACLE_CREVICE].getEnabled()) {
  
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

  }


  // Should we launch a ramp ?
  
  bool launch = true;
  
  if (!obstacles[OBSTACLE_CREVICE].getEnabled()) {

    for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {

      if (cars[idx].getEnabled() && cars[idx].getX().getInteger() > (WIDTH / 4)) { 
        launch = false;
        break;
      }

    }

    for (idx = 0; idx < NUMBER_OF_OBSTACLES; ++idx) {

      if (obstacles[idx].getEnabled()) { 
        launch = false;
        break;
      }

    }

    if (launch) {
      
      idx = random(0, 20);
      
      if (idx == 17){

Serial.println("Launch Ramp ");

          obstacles[OBSTACLE_RAMP].setObstacleType(ObstacleType::Ramp);
          obstacles[OBSTACLE_RAMP].setEnabled(true);
          obstacles[OBSTACLE_RAMP].setX(WIDTH);
          obstacles[OBSTACLE_RAMP].setY(random(road.y + ROAD_OFFSET_UPPER + 4 , road.y + road.height - 6 - obstacles[3].getHeight()));
          obstacles[OBSTACLE_RAMP].setBitmap(obstacle_images[(uint8_t)ObstacleType::Ramp]); 
          obstacles[OBSTACLE_RAMP].setMask(obstacle_masks[(uint8_t)ObstacleType::Ramp]); 

          obstacles[OBSTACLE_CREVICE].setObstacleType(ObstacleType::Crevice);
          obstacles[OBSTACLE_CREVICE].setEnabled(true);
          obstacles[OBSTACLE_CREVICE].setX(WIDTH + 40);
          obstacles[OBSTACLE_CREVICE].setY(road.y + 2);
          obstacles[OBSTACLE_CREVICE].setBitmap(obstacle_images[(uint8_t)ObstacleType::Crevice]); 
          obstacles[OBSTACLE_CREVICE].setMask(obstacle_masks[(uint8_t)ObstacleType::Crevice]); 
          
      }
      
    }
    
  }


  // Update the position of the obstacles .. (they don't move).
  
  for (idx = 0; idx < NUMBER_OF_OBSTACLES_INC_RAMP; ++idx) {
    if (obstacles[idx].getEnabled()) { 
      obstacles[idx].move(scrollIncrement); 
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

  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {

    if (cars[idx].getEnabled()) {
      
      if (arduboy.collide(player.getNewRect(), cars[idx].getNewRect())) {
  
  
        // Only move the car back once - even if it is touching multiple cars ..
        
        if (!collisionAlreadyDetected) { 
          player.setX(player.getX() - 0.4);
          sound.tones(sound_bump); 
          collisionAlreadyDetected = true;
        }
  
        cars[idx].setNewX(cars[idx].getX() + 0.4);
        
      }
      
    }
        
  }


  // Are any cars touching other cars ?  Sort the cars into order so that the left most is processed first ..

  sortArray(cars, 3, sortByNewX);

  bool checkCars = true;

  while (checkCars) {  
    
    checkCars = false;

    for (uint8_t left = 0; left < NUMBER_OF_CARS; ++left) {
      
      if (cars[left].getEnabled()) {
    
        for (uint8_t right = left + 1; right < NUMBER_OF_CARS; ++right) {
      
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


              // We are about to move one of the cars so this test will need to be done again ..

              checkCars = true;
              cars[right].setNewX(cars[right].getNewX() + 2);


              // Check to see if the new placement of the car is still causing a collision. If 
              // so bump the car up or down depending on which way the car has moved already ..
              
              if (arduboy.collide( cars[left].getNewRect(), cars[right].getNewRect() )) {
               
                if (cars[right].getDeltaY() < 0) { 
                  cars[right].setNewY(cars[right].getNewY() + 1); 
                }
                else if (cars[right].getDeltaY() > 0) { 
                  cars[right].setNewY(cars[right].getNewY() - 1); 
                }

              }

            }
  
          }
  
        }
    
      }
  
    }
    
  }


  // Update the position of the player and the cars ..
  
  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {
    if (cars[idx].getEnabled()) { cars[idx].updatePosition(); }
  }

  
  drawRoad();

  for (idx = 0; idx < NUMBER_OF_OBSTACLES_INC_RAMP; ++idx) {
    obstacles[idx].renderImage(frame);
  }
  
  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {
    cars[idx].renderImage(frame);
  }

  player.renderImage(frame);

  renderScoreboard();

  arduboy.display();
  delay(10);
  
  if (arduboy.pressed(A_BUTTON)) {
    delay(60);

    /* Debug car position */
//    Serial.print("(player.getX().getInteger() : ");
//    Serial.print(player.getX().getInteger());
//    Serial.print(", getRoadElement_UpperLimit(player.getX().getInteger()) + ROAD_OFFSET_UPPER : ");
//    Serial.print(getRoadElement_UpperLimit(player.getX().getInteger()) + ROAD_OFFSET_UPPER);
//    Serial.print(", getRoadElement_LowerLimit(player.getX()) + ROAD_OFFSET_LOWER : ");
//    Serial.println(getRoadElement_LowerLimit(player.getX().getInteger()) + ROAD_OFFSET_LOWER);
debugRoad();
  }
  if (arduboy.pressed(B_BUTTON)) {
    delay(250);
  }
  
}
void debugRoad() {

  for (int x = 0; x < 17; x++) {
    Serial.print("{");
    Serial.print(roadElements[x].upperLimit);
    Serial.print(",");
    Serial.print(roadElements[x].lowerLimit);
    Serial.print(",");
    Serial.print((int)roadElements[x].roadType);
    Serial.print("}");
  }

  Serial.println(" ");

}

/* -----------------------------------------------------------------------------------------------------------------------------
 *  Render the scorebaord.
 *  
 *  The scorebaord alternates between two modes - points and fuel.
 */
uint16_t scoreFrameCnt;
uint16_t scoreFuelFlash;

#define SCOREBOARD_FUEL_FLASH_MAX       30
#define SCOREBOARD_FRAME_COUNT_MAX      200
#define SCOREBOARD_NUMBER_OF_FRAMES     2

#define SCOREBOARD_OUTER_RECT_X         99
#define SCOREBOARD_OUTER_RECT_Y         0
#define SCOREBOARD_OUTER_RECT_WIDTH     29
#define SCOREBOARD_OUTER_RECT_HEIGHT    12

#define SCOREBOARD_INNER_RECT_X         SCOREBOARD_OUTER_RECT_X + 1
#define SCOREBOARD_INNER_RECT_Y         SCOREBOARD_OUTER_RECT_Y
#define SCOREBOARD_INNER_RECT_WIDTH     SCOREBOARD_OUTER_RECT_WIDTH - 1
#define SCOREBOARD_INNER_RECT_HEIGHT    SCOREBOARD_OUTER_RECT_HEIGHT - 1

#define SCOREBOARD_ICON_X               103
#define SCOREBOARD_ICON_Y               2
#define SCOREBOARD_DIGIT_1_X            111
#define SCOREBOARD_DIGIT_2_X            116
#define SCOREBOARD_DIGIT_3_X            121
#define SCOREBOARD_DIGIT_Y              2

#define SCOREBOARD_FUEL_BAR_TOP         2
#define SCOREBOARD_FUEL_BAR_BOTTOM      8
#define SCOREBOARD_FUEL_BAR_LEFT        110

void renderScoreboard() {

   uint16_t player_score = player.getScore();


   // Increment the frame count

   ++scoreFuelFlash;  if (scoreFuelFlash > SCOREBOARD_FUEL_FLASH_MAX) { scoreFuelFlash = 0; }
   ++scoreFrameCnt;  if (scoreFrameCnt > (SCOREBOARD_FRAME_COUNT_MAX * SCOREBOARD_NUMBER_OF_FRAMES)) { scoreFrameCnt = 0; }


   // Clear the board space ..
   
  arduboy.fillRect(SCOREBOARD_OUTER_RECT_X, SCOREBOARD_OUTER_RECT_Y, SCOREBOARD_OUTER_RECT_WIDTH, SCOREBOARD_OUTER_RECT_HEIGHT, BLACK);
  arduboy.drawRect(SCOREBOARD_INNER_RECT_X, SCOREBOARD_INNER_RECT_Y, SCOREBOARD_INNER_RECT_WIDTH, SCOREBOARD_INNER_RECT_HEIGHT, WHITE);

  switch (scoreFrameCnt / SCOREBOARD_FRAME_COUNT_MAX) {

    case 0:
    
      Sprites::drawOverwrite(SCOREBOARD_ICON_X, SCOREBOARD_ICON_Y, jewel, frame);
      Sprites::drawOverwrite(SCOREBOARD_DIGIT_1_X, SCOREBOARD_DIGIT_Y, digits[player_score / 100], frame);
      player_score = player_score - (player_score / 100) * 100;
      Sprites::drawOverwrite(SCOREBOARD_DIGIT_2_X, SCOREBOARD_DIGIT_Y, digits[player_score / 10], frame);
      Sprites::drawOverwrite(SCOREBOARD_DIGIT_3_X, SCOREBOARD_DIGIT_Y, digits[player_score % 10], frame);
     
      break;

    case 1:
    
      Sprites::drawOverwrite(SCOREBOARD_ICON_X, SCOREBOARD_ICON_Y, fuel_gauge, frame);
      if ((player.getFuel() <= 4 && scoreFuelFlash >= (SCOREBOARD_FUEL_FLASH_MAX / 2)) || player.getFuel() > 4) {
        for (idx = 0; idx<player.getFuel().getInteger(); idx+=2) {
          arduboy.drawLine(SCOREBOARD_FUEL_BAR_LEFT + idx, SCOREBOARD_FUEL_BAR_TOP, SCOREBOARD_FUEL_BAR_LEFT + idx, SCOREBOARD_FUEL_BAR_BOTTOM);
        }
      }

      break;
    
  }

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Get the upper limit of the road at position X
 */
const int16_t getRoadElement_UpperLimit(SQ15x16 x) {

  return (x.getInteger() + road.x ? roadElements[((x.getInteger() + road.x) / 8)].upperLimit : roadElements[0].upperLimit);
  
}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Get the lower limit of the road at position X
 */
const int16_t getRoadElement_LowerLimit(SQ15x16 x) {

  return (x.getInteger() + road.x >= 0 ? roadElements[((x.getInteger() + road.x) / 8)].lowerLimit : roadElements[0].lowerLimit);

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
  cars[carNumber].setSteeringType(SteeringType::FollowRoad);

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Launch a new obstacle onto the road.
 * -----------------------------------------------------------------------------------------------------------------------------
 */
 void launchObstacle(uint8_t obstacleNumber) {

  ObstacleType type;

//Serial.println(static_cast<float>(player.getFuel()));

  if (player.getFuel() <= 4) {
    type = ObstacleType::Fuel;
  }
  else {
    type = (ObstacleType)random((uint8_t)ObstacleType::First, (uint8_t)ObstacleType::Count);
  }
  
  switch (type) {
    
    case ObstacleType::RoughRoad:
      obstacles[obstacleNumber].setObstacleType(ObstacleType::RoughRoad);
      obstacles[obstacleNumber].setEnabled(true);
      obstacles[obstacleNumber].setX(WIDTH);
      obstacles[obstacleNumber].setY(random(road.y + ROAD_OFFSET_UPPER + 4 , road.y + road.height - 6 - obstacles[obstacleNumber].getHeight()));
      obstacles[obstacleNumber].setBitmap(obstacle_images[(uint8_t)ObstacleType::RoughRoad]); 
      obstacles[obstacleNumber].setMask(obstacle_masks[(uint8_t)ObstacleType::RoughRoad]); 
      break;
    
    case ObstacleType::Crossing:  
      obstacles[obstacleNumber].setObstacleType(ObstacleType::Crossing);
      obstacles[obstacleNumber].setEnabled(true);
      obstacles[obstacleNumber].setX(WIDTH);
      obstacles[obstacleNumber].setY(road.y + ROAD_OFFSET_UPPER + 3);
      obstacles[obstacleNumber].setBitmap(obstacle_images[(uint8_t)ObstacleType::Crossing]); 
      obstacles[obstacleNumber].setMask(obstacle_masks[(uint8_t)ObstacleType::Crossing]); 
      break;
    
    case ObstacleType::Fuel: 
      obstacles[obstacleNumber].setObstacleType(ObstacleType::Fuel);
      obstacles[obstacleNumber].setEnabled(true);
      obstacles[obstacleNumber].setX(WIDTH);
      obstacles[obstacleNumber].setY(random(road.y + ROAD_OFFSET_UPPER + 4 , road.y + road.height - 6 - obstacles[obstacleNumber].getHeight()));
      obstacles[obstacleNumber].setBitmap(obstacle_images[(uint8_t)ObstacleType::Fuel]); 
      obstacles[obstacleNumber].setMask(obstacle_masks[(uint8_t)ObstacleType::Fuel]); 
      break;
    
    case ObstacleType::Jewel: 
      obstacles[obstacleNumber].setObstacleType(ObstacleType::Jewel);
      obstacles[obstacleNumber].setEnabled(true);
      obstacles[obstacleNumber].setX(WIDTH);
      obstacles[obstacleNumber].setY(random(road.y + ROAD_OFFSET_UPPER + 4 , road.y + road.height - 6 - obstacles[obstacleNumber].getHeight()));
      obstacles[obstacleNumber].setBitmap(obstacle_images[(uint8_t)ObstacleType::Jewel]); 
      obstacles[obstacleNumber].setMask(obstacle_masks[(uint8_t)ObstacleType::Jewel]); 
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
      
      if (road.randomNumber > 0 || (obstacles[OBSTACLE_CREVICE].getEnabled() && obstacles[OBSTACLE_CREVICE].getX().getInteger() > 90)) {
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
        if (road.y > ROAD_Y_MIN) {
          road.y-=2;
          road.type = RoadType::Up;
        }
        break;
        
      case RoadType::Down:
        if (road.y < ROAD_Y_MAX) {   // height = 64, -2 height = 72, -4 height = 68, -10
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


/* -----------------------------------------------------------------------------------------------------------------------------
 *  If the player was to move up, would they crash into another car?
 */
bool collideWithCarAbove() {

  player.setNewX(player.getX());
  player.setNewY(player.getY() - static_cast<SQ15x16>(0.5));

  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {
      
    if (cars[idx].getEnabled()) { 

      if (collide(player.getNewRect(), cars[idx].getRect(), Direction::Up)) {
        return true;
      }

    }

  }

  return false;
  
}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  If the player was to move down, would they crash into another car?
 */
bool collideWithCarBelow() {

  player.setNewX(player.getX());
  player.setNewY(player.getY() + static_cast<SQ15x16>(0.5));

  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {

    if (cars[idx].getEnabled()) { 

      if (collide(player.getNewRect(), cars[idx].getRect(), Direction::Down)) {
        return true;
      }

    }

  }

  return false;
  
}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  If the player was to move forward, would they crash into another car?
 */
bool collideWithCarInFront() {

  player.setNewX(player.getX());
  player.setNewY(player.getY() + static_cast<SQ15x16>(0.5));

  for (idx = 0; idx < NUMBER_OF_CARS; ++idx) {

    if (cars[idx].getEnabled()) { 

      if (collide(player.getNewRect(), cars[idx].getRect(), Direction::Right)) {
        return true;
      }

    }

  }

  return false;
  
}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Determine if the Rect1 has collided with Rect2 in the nominated direction.
 *       
 *  Note that the direction is relative to Rect1.       
 */
bool collide(Rect rect1, Rect rect2, Direction testDirection) {
  
  return (collide(rect1, rect2) & testDirection) == testDirection;
  
}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Determine on which sides two Rects may have collided.
 *       
 *  Note that the returned directions are relative to Rect1.       
 */
Direction collide(Rect rect1, Rect rect2) {

  Direction direction = Direction::None;
 
  if (!(rect2.x                >= rect1.x + rect1.width  ||
        rect2.x + rect2.width  <= rect1.x                ||
        rect2.y                >= rect1.y + rect1.height ||
        rect2.y + rect2.height <= rect1.y)) {

    if ((rect1.x < rect2.x) && (rect1.x + rect1.width > rect2.x))    direction = direction | Direction::Right;     // Rect 2 is to the right of Rect 1?
    if ((rect2.x < rect1.x) && (rect2.x + rect2.width > rect1.x))    direction = direction | Direction::Left;      // Rect 2 is to the left of Rect 1?
    if ((rect2.y < rect1.y) && (rect2.y + rect2.height > rect1.y))   direction = direction | Direction::Up;        // Rect 2 is above Rect 1?
    if ((rect1.y < rect2.y) && (rect1.y + rect1.height > rect2.y))   direction = direction | Direction::Down;      // Rect 2 is below Rect 1?

  }

  return direction;

}

//bool rampVisible() {
//
//  for (idx = 0; idx < NUMBER_OF_OBSTACLES; ++idx) {
//    if (obstacles[idx].getEnabled() && obstacles[idx].getObstacleType() == Obstacle::Ramp) return true;
//  }
//
//  return false;
//  
//}

