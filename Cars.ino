#include <Arduboy2.h>
#include "Car.h"
#include "Player.h"
#include "Images.h" 
#include "Enums.h"
#include "Sort.h"

Arduboy2 arduboy; 

#define NUMBER_OF_CAR_IMAGES  8
#define NUMBER_OF_CARS        3
#define ROAD_IMAGES_HEIGHT    24

#define ROAD_OFFSET_UPPER 22
#define ROAD_OFFSET_LOWER 2

const uint8_t scrollIncrement = 2;
const uint8_t frame = 0;

RoadElement roadElements[17];
Road road = { 0, -16, 64, RoadType::Straight, 0, 2 };
Player player = {20, 24, car_player, mask_player};

const byte* car_images[] = { car_01, car_02, car_03, car_04, car_05, car_06, car_07, car_08 };
const byte* car_masks[] =  { mask_01, mask_02, mask_03, mask_04, mask_05, mask_06, mask_07, mask_08 };

Car cars[3] = {
  {1, -80, 0, 0, car_images[2], car_masks[2], cars, SteeringType::ZigZag},
  {2, -80, 0, 0, car_images[3], car_masks[3], cars, SteeringType::ZigZag},
  {3, -80, 0, 0, car_images[4], car_masks[4], cars, SteeringType::ZigZag}
};

int16_t idx = 0; // scratch variable.
int8_t launchCountdown = 70;


bool sortByNewX(Car x, Car y) {
  
  if (x.getNewX() > y.getNewX()) {
    return true;
  } 
  else {
    return false;
  }
  
}

void setup() {
  
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();

  cars[0].renderImage(frame);
  cars[1].renderImage(frame);
  cars[2].renderImage(frame);

  for (idx = 0; idx < 17; ++idx) {

    roadElements[idx].upperLimit = -16;
    roadElements[idx].lowerLimit = road.height + -16;
    roadElements[idx].roadType = RoadType::Straight;
    
  }

  arduboy.clear();
  arduboy.display();

}


void loop() {

  player.clearImage(frame);

  cars[0].clearImage(frame);
  cars[1].clearImage(frame);
  cars[2].clearImage(frame);

//  if (arduboy.pressed(UP_BUTTON) && player.y > getRoadElement_UpperLimit(player.x) + ROAD_OFFSET_UPPER)                      { player.y--; }
//  if (arduboy.pressed(DOWN_BUTTON) && player.y < getRoadElement_LowerLimit(player.x) + ROAD_OFFSET_LOWER - player.height)    { player.y++; }

  if (arduboy.pressed(UP_BUTTON) && player.getY() > 0)                                { player.setNewY(player.getY() - static_cast<SQ7x8>(0.5)); }
  if (arduboy.pressed(DOWN_BUTTON) && player.getY() < HEIGHT - player.getHeight())    { player.setNewY(player.getY() + static_cast<SQ7x8>(0.5)); }
  if (arduboy.pressed(LEFT_BUTTON) && player.getX() > 0)                              { player.setNewX(player.getX() - static_cast<SQ7x8>(0.75)); }
  if (arduboy.pressed(RIGHT_BUTTON) && player.getX() < 64)                            { player.setNewX(player.getX() + static_cast<SQ7x8>(1.00)); }
 
  //scrollBuffer(scrollIncrement);


  --launchCountdown;
  
  if (launchCountdown == 0) {

    for (uint8_t carNumber = 0; carNumber < NUMBER_OF_CARS; ++carNumber) {

      if (!cars[carNumber].getEnabled()) { 
        launchCar(carNumber); 
        break;
      }

    }

    launchCountdown = random(60, 120);
            
  }


  if (player.getY().GetInteger() < getRoadElement_UpperLimit(player.getX()) + ROAD_OFFSET_UPPER)                         { player.setNewX(player.getX() - static_cast<SQ7x8>(0.4)); }
  if (player.getY().GetInteger() + player.getHeight() > getRoadElement_LowerLimit(player.getX()) + ROAD_OFFSET_LOWER)    { player.setNewX(player.getX() - static_cast<SQ7x8>(0.4)); }

  if (cars[0].getEnabled()) { cars[0].calcNewPosition(scrollIncrement, getRoadElement_UpperLimit(cars[0].getX()) + ROAD_OFFSET_UPPER, getRoadElement_LowerLimit(cars[0].getX()) + ROAD_OFFSET_LOWER); }
  if (cars[1].getEnabled()) { cars[1].calcNewPosition(scrollIncrement, getRoadElement_UpperLimit(cars[1].getX()) + ROAD_OFFSET_UPPER, getRoadElement_LowerLimit(cars[1].getX()) + ROAD_OFFSET_LOWER); }
  if (cars[2].getEnabled()) { cars[2].calcNewPosition(scrollIncrement, getRoadElement_UpperLimit(cars[2].getX()) + ROAD_OFFSET_UPPER, getRoadElement_LowerLimit(cars[2].getX()) + ROAD_OFFSET_LOWER); }


  // Is the player touching any other cars?

  bool collision = false;


  for (idx = 0; idx < 3; ++idx) {

    if (arduboy.collide(player.getNewRect(), cars[idx].getNewRect())) {

      if (!collision) {
        player.setNewX(player.getX() - static_cast<SQ7x8>(0.4));
        collision = true;
      }

      cars[idx].setNewX(cars[idx].getX() + static_cast<SQ7x8>(0.4));
      
    }
    
  }


  // Are any cars touching other cars ?
//sortArray(cars, 3, sortByNewX);

    
  for (uint8_t j = 0; j < 3; ++j) {

    bool collisions_XY = false;
    bool collisions_X = false;
    bool collisions_Y = false;

    for (uint8_t i = 0; i < 3; ++i) {
  
      if (i != j && cars[i].getEnabled()) {
        
        if (arduboy.collide(cars[i].getNewRect(), cars[j].getNewRect())) {

          collisions_XY = true;

          if (arduboy.collide(cars[i].getNewRect(), cars[j].getRect(cars[j].getNewX().GetInteger(), cars[j].getY().GetInteger()))) {

            collisions_X = true;
            
          }

          else if (arduboy.collide(cars[i].getNewRect(), cars[j].getRect(cars[j].getX().GetInteger(), cars[j].getNewY().GetInteger()))) {

            collisions_Y = true;

          }
  
          break;
  
        }
  
      }
  
    }

Serial.print("collisions_XY : ");
Serial.print(collisions_XY);
Serial.print(", collisions_X : ");
Serial.print(collisions_X);
Serial.print(", collisions_Y : ");
Serial.print(collisions_Y);
Serial.println("");

    if (collisions_XY) {
//Serial.println("collisions_XY");      
     
      if (collisions_X) { 
//Serial.println("collisions_X");      
        cars[j].setNewX(cars[j].getX()); 
      }
      else  if (collisions_Y) { 
//Serial.println("collisions_Y");      
        cars[j].setNewY(cars[j].getY()); 
      }

    }

  }



  player.updatePosition();
  if (cars[0].getEnabled()) { cars[0].updatePosition(); }
  if (cars[1].getEnabled()) { cars[1].updatePosition(); }
  if (cars[2].getEnabled()) { cars[2].updatePosition(); }




  
  drawScenery();
  
 
  cars[0].renderImage(frame);
  cars[1].renderImage(frame);
  cars[2].renderImage(frame);

  player.renderImage(frame);
  
  arduboy.display();
  delay(10);
  
  if (arduboy.pressed(A_BUTTON)) {
    delay(60);
/*    Serial.print("road.y: ");
    Serial.print(road.y);
    Serial.print(", road.y  + ROAD_OFFSET_UPPER + 4: ");
    Serial.print(road.y  + ROAD_OFFSET_UPPER + 4);
    Serial.print(", road.y  + ROAD_OFFSET_LOWER + road.height - 18: ");
    Serial.println(road.y  + ROAD_OFFSET_LOWER + road.height - 6);
    */
    Serial.print("(player.getX().GetInteger() : ");
    Serial.print(player.getX().GetInteger());
    Serial.print(", getRoadElement_UpperLimit(player.getX().GetInteger()) + ROAD_OFFSET_UPPER : ");
    Serial.print(getRoadElement_UpperLimit(player.getX().GetInteger()) + ROAD_OFFSET_UPPER);
    Serial.print(", getRoadElement_LowerLimit(player.getX()) + ROAD_OFFSET_LOWER : ");
    Serial.println(getRoadElement_LowerLimit(player.getX().GetInteger()) + ROAD_OFFSET_LOWER);

  }
  if (arduboy.pressed(B_BUTTON)) {
    delay(720);
  }
  
}

void drawScenery() {

  if (road.x == 8) {
      
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

     
//   Serial.print(F("Before : "));
//    debugRoad();
   
	RoadElement * pt = roadElements;
	memmove(static_cast<void*>(&pt[0]), static_cast<const void*>(&pt[1]), 16 * sizeof(RoadElement));

//   Serial.print("After  : ");
//    debugRoad();


    roadElements[16].upperLimit = road.y;
    roadElements[16].lowerLimit = road.y + road.height;
    roadElements[16].roadType = road.type;

  }

  for (idx = 0; idx < 17; ++idx) {
 
    int8_t upperLimitOffset = 0;
    int8_t lowerLimitOffset = 0;
  
    switch (roadElements[idx].roadType) {
      
      case RoadType::Straight:
        break;
       
      case RoadType::Up:
        upperLimitOffset = 0;
        break;
       
      case RoadType::Down:
        lowerLimitOffset = 0; 
        break;
        
    }

    Sprites::drawOverwrite((idx * 8) - road.x, roadElements[idx].upperLimit + upperLimitOffset, upper_road, frame);   
    Sprites::drawOverwrite((idx * 8) - road.x, roadElements[idx].lowerLimit + lowerLimitOffset, lower_road, frame);   

  }

  road.x+=scrollIncrement;

}


const int16_t getRoadElement_UpperLimit(SQ7x8 x) {

  return (x + road.x >= 0 ? roadElements[((x.GetInteger() + road.x) / 8)].upperLimit : roadElements[0].upperLimit);
  
}


const int16_t getRoadElement_LowerLimit(SQ7x8 x) {

  return (x+road.x >= 0 ? roadElements[((x.GetInteger() + road.x) / 8)].lowerLimit : roadElements[0].lowerLimit);

}

void launchCar(uint8_t carNumber) {

  idx = random(0, NUMBER_OF_CAR_IMAGES);
  
  cars[carNumber].setX(WIDTH);
  cars[carNumber].setEnabled(true);
  cars[carNumber].setBitmap(car_images[idx]); 
  cars[carNumber].setMask(car_masks[idx]); 
  cars[carNumber].setY(random(road.y  + ROAD_OFFSET_UPPER + 4 , road.y + road.height - 6 - cars[carNumber].getHeight()));
  cars[carNumber].setSpeedX((random(-180, -40) / 100.0));
  cars[carNumber].setSpeedY((random(20, 5) / 100.0));

  cars[carNumber].setSteeringType(static_cast<SteeringType> (random((uint8_t)SteeringType::First, (uint8_t)SteeringType::Count)));
//  cars[carNumber].setSteeringType(SteeringType::Random);

}


