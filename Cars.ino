#include <Arduboy2.h>
#include "Car.h"
#include "Images.h" 
#include "Enums.h"

Arduboy2 arduboy; 

#define BUFFER_ROW_0_START    0
#define BUFFER_ROW_1_START    BUFFER_ROW_0_START + WIDTH
#define BUFFER_ROW_2_START    BUFFER_ROW_1_START + WIDTH
#define BUFFER_ROW_3_START    BUFFER_ROW_2_START + WIDTH
#define BUFFER_ROW_4_START    BUFFER_ROW_3_START + WIDTH
#define BUFFER_ROW_5_START    BUFFER_ROW_4_START + WIDTH
#define BUFFER_ROW_6_START    BUFFER_ROW_5_START + WIDTH
#define BUFFER_ROW_7_START    BUFFER_ROW_6_START + WIDTH

#define NUMBER_OF_CAR_IMAGES  8
#define NUMBER_OF_CARS        3
#define ROAD_IMAGES_HEIGHT    24

const uint8_t scrollIncrement = 2;
const uint8_t frame = 0;

RoadElement roadElements[17];
Road road = { 0, -16, 64, RoadType::Straight, 0, 2 };
Player player = {0, 24, 14, 16};

const byte* car_images[] = { car_01,     car_02,     car_03,     car_04,     car_05,     car_06,     car_07,     car_08 };
const byte* car_masks[] =  { mask_20_12, mask_19_12, mask_16_10, mask_19_12, mask_18_10, mask_17_13, mask_17_14, mask_19_15 };

Car cars[3] = {
  {1, /*&arduboy,*/ 80,  16, -4,  car_images[2], car_masks[2], cars, SteeringType::FollowRoad},
  {2, /*&arduboy,*/ 128, 32, -10, car_images[3], car_masks[3], cars, SteeringType::FollowRoad},
  {3, /*&arduboy,*/ 128, 48, -8,  car_images[4], car_masks[4], cars, SteeringType::ZigZag}
};

uint8_t idx = 0; // scratch variable.

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
  
 // if (!(arduboy.nextFrame())) return;
//arduboy.clear();


  Sprites::drawErase(player.x, player.y, car_player, frame);
  cars[0].clearImage(frame);
  cars[1].clearImage(frame);
  cars[2].clearImage(frame);

  if (arduboy.pressed(UP_BUTTON) && player.y > 0)                           { player.y--; }
  if (arduboy.pressed(DOWN_BUTTON) && player.y < HEIGHT - player.height)    { player.y++; }
  if (arduboy.pressed(LEFT_BUTTON) && player.x > 0)                         { player.x--; }
  if (arduboy.pressed(RIGHT_BUTTON) && player.x < 64)                       { player.x++; }
 
  //scrollBuffer(scrollIncrement);

  drawScenery();
  Serial.println("===----====-----===----===");
  Serial.println("Cars[0] 1");
  cars[0].move(scrollIncrement, road.x + ROAD_IMAGES_HEIGHT, road.x + road.height + ROAD_IMAGES_HEIGHT);
  Serial.println("Cars[1] 2");
  cars[1].move(scrollIncrement, road.x + ROAD_IMAGES_HEIGHT, road.x + road.height + ROAD_IMAGES_HEIGHT);
  Serial.println("Cars[2] 3");
  cars[2].move(scrollIncrement, road.x + ROAD_IMAGES_HEIGHT, road.x + road.height + ROAD_IMAGES_HEIGHT);

//Serial.println("_____");
//Serial.println(cars[0].getName());
//Serial.println(cars[1].getName());
//Serial.println(cars[2].getName());
  if (!cars[0].getEnabled()) { 
    idx = random(0, NUMBER_OF_CAR_IMAGES);
    cars[0].setX(WIDTH);
    cars[0].setEnabled(true);
    cars[0].setBitmap(car_images[idx]); 
    cars[0].setMask(car_masks[idx]); 
  }

  if (!cars[1].getEnabled()) {  
    idx = random(0, NUMBER_OF_CAR_IMAGES);
    cars[1].setX(WIDTH);
    cars[1].setEnabled(true);
    cars[1].setBitmap(car_images[idx]); 
    cars[1].setMask(car_masks[idx]); 
 }
  
  if (!cars[2].getEnabled()) {  
    idx = random(0, NUMBER_OF_CAR_IMAGES);
    cars[2].setX(WIDTH);
    cars[2].setEnabled(true);
    cars[2].setBitmap(car_images[idx]); 
    cars[2].setMask(car_masks[idx]); 
  }
  
  cars[0].renderImage(frame);
  cars[1].renderImage(frame);
  cars[2].renderImage(frame);
  
  Sprites::drawExternalMask(player.x, player.y, car_player, mask_16_14, frame, frame);
  
  arduboy.display();
  delay(10);
  
}

void drawScenery() {

  if (road.x == 8) {
      
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

    road.x = 0;

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

     
//   Serial.print("Before : ");
//    debugRoad();
   
    int pt = roadElements;
    memmove (pt, pt + sizeof(RoadElement), 16 * sizeof(RoadElement));

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
        upperLimitOffset = +2;
        break;
       
      case RoadType::Down:
        lowerLimitOffset = -2; 
        break;
        
    }

    Sprites::drawOverwrite((idx * 8) - road.x, roadElements[idx].upperLimit + upperLimitOffset, upper_road, frame);   
    Sprites::drawOverwrite((idx * 8) - road.x, roadElements[idx].lowerLimit + lowerLimitOffset, lower_road, frame);   

  }

  road.x+=scrollIncrement;
  //delay(10);
  
}

void debugRoad() {

  for (int x = 0; x < 17; ++x) {
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

void scrollBuffer(byte scrollIncrement) { 

  memmove (arduboy.sBuffer + BUFFER_ROW_0_START, arduboy.sBuffer + BUFFER_ROW_0_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_1_START, arduboy.sBuffer + BUFFER_ROW_1_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_2_START, arduboy.sBuffer + BUFFER_ROW_2_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_3_START, arduboy.sBuffer + BUFFER_ROW_3_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_4_START, arduboy.sBuffer + BUFFER_ROW_4_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_5_START, arduboy.sBuffer + BUFFER_ROW_5_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_6_START, arduboy.sBuffer + BUFFER_ROW_6_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_7_START, arduboy.sBuffer + BUFFER_ROW_7_START + scrollIncrement, WIDTH - scrollIncrement);

  memset (arduboy.sBuffer + BUFFER_ROW_0_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_1_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_2_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_3_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_4_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_5_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_6_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_7_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  
}
