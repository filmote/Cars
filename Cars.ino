#include <Arduboy2.h>
#include "Car.h"
#include "Images.h" 

Arduboy2 arduboy;
Sprites sprites;

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

const int scrollIncrement = 2;
int frame = 0;

enum class RoadType : uint8_t {
  Straight,
  Up,  
  Down,
  Count,
  First = Straight,
  Last = Down,
};

struct RoadElement {
  int upperLimit;
  int lowerLimit;
  RoadType roadType;
};

RoadElement roadElements[17];

struct Road {
  int x;
  int y;
  int height;
  RoadType type;
  int randomNumber;
  int randomCount;
};
Road road = { 0, -16, 64, RoadType::Straight, 0, 2 };

struct Player {
  byte x;
  byte y;
  const byte height;
  const byte width;
};
Player player = {0, 24, 14, 16};

/*
Car car1 = Car(1);
Car car2 = Car(2);
Car car3 = Car(3);
*/
const byte* car_images[] = { car_01,     car_02,     car_03,     car_04,     car_05,     car_06,     car_07,     car_08 };
const byte* car_masks[] =  { mask_20_12, mask_19_12, mask_16_10, mask_19_12, mask_18_10, mask_17_13, mask_17_14, mask_19_15 };
//Car* cars[] = { &car1, &car2, &car3 };
Car cars[3] = { 1, 2, 3};
byte idx = 0; // scratch variable.

void setup() {
  
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
  
  cars[0].setArduboy(arduboy);
  cars[0].setCars(cars);
  cars[0].setX(80);
  cars[0].setY(48);
  cars[0].bitmap = car_images[7];
  cars[0].mask = car_masks[7];
  cars[0].setSpeed(-4);
  cars[0].setEnabled(true);
  cars[0].renderImage(frame);
  
  cars[1].setArduboy(arduboy);
  cars[1].setCars(cars);
  cars[1].setX(128);
  cars[1].setY(32);
  cars[1].bitmap = car_images[4];
  cars[1].mask = car_masks[4];
  cars[1].setEnabled(true);
  cars[1].setSpeed(-10);
  cars[1].renderImage(frame);
  
  cars[2].setArduboy(arduboy);
  cars[2].setCars(cars);
  cars[2].setX(128);
  cars[2].setY(16);
  cars[2].bitmap = car_03;
  cars[2].mask = mask_16_10;
  cars[2].setSpeed(-8);
  cars[2].setEnabled(true);
  cars[2].renderImage(frame);

  for (int x = 0; x < 17; x++) {

    roadElements[x].upperLimit = -16;
    roadElements[x].lowerLimit = road.height + -16;
    roadElements[x].roadType = RoadType::Straight;
    
  }

  arduboy.clear();
  arduboy.display();

}


void loop() {
  
 // if (!(arduboy.nextFrame())) return;
//arduboy.clear();


  sprites.drawErase(player.x, player.y, car_player, frame);
  cars[0].clearImage(frame);
  cars[1].clearImage(frame);
  cars[2].clearImage(frame);

  if (arduboy.pressed(UP_BUTTON) && player.y > 0)                           { player.y--; }
  if (arduboy.pressed(DOWN_BUTTON) && player.y < HEIGHT - player.height)    { player.y++; }
  if (arduboy.pressed(LEFT_BUTTON) && player.x > 0)                         { player.x--; }
  if (arduboy.pressed(RIGHT_BUTTON) && player.x < 64)                       { player.x++; }
 
  //scrollBuffer(scrollIncrement);

  drawScenery();
  
  cars[0].scroll(scrollIncrement);
  cars[1].scroll(scrollIncrement);
  cars[2].scroll(scrollIncrement);

  if (!cars[0].getEnabled()) { 
    idx = random(0, NUMBER_OF_CAR_IMAGES);
    cars[0].setX(WIDTH);
    cars[0].setEnabled(true);
    cars[0].bitmap = car_images[idx]; 
    cars[0].mask = car_masks[idx]; 
  }

  if (!cars[1].getEnabled()) {  
    idx = random(0, NUMBER_OF_CAR_IMAGES);
    cars[1].setX(WIDTH);
    cars[1].setEnabled(true);
    cars[1].bitmap = car_images[idx]; 
    cars[1].mask = car_masks[idx]; 
  }
  
  if (!cars[2].getEnabled()) {  
    idx = random(0, NUMBER_OF_CAR_IMAGES);
    cars[2].setX(WIDTH);
    cars[2].setEnabled(true);
    cars[2].bitmap = car_images[idx]; 
    cars[2].mask = car_masks[idx]; 
  }
  
  cars[0].renderImage(frame);
  cars[1].renderImage(frame);
  cars[2].renderImage(frame);
  
  sprites.drawExternalMask(player.x, player.y, car_player, mask_16_14, frame, frame);
  
  arduboy.display();
//  delay(20);
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

     
//    Serial.print("Before : ");
//    debugRoad();
   
    int pt = roadElements;
    memmove (pt, pt + sizeof(RoadElement), 16 * sizeof(RoadElement));

//    Serial.print("After  : ");
//    debugRoad();


    roadElements[16].upperLimit = road.y;
    roadElements[16].lowerLimit = road.y + road.height;
    roadElements[16].roadType = road.type;

  }

  for (int x = 0; x < 17; x++) {
   
    switch (roadElements[x].roadType) {
      
      case RoadType::Straight:
        sprites.drawOverwrite((x*8) - road.x, roadElements[x].upperLimit, upper_road, frame);   
        sprites.drawOverwrite((x*8) - road.x, roadElements[x].lowerLimit, lower_road, frame);   
        break;
       
      case RoadType::Up:
        sprites.drawOverwrite((x*8) - road.x, roadElements[x].upperLimit + 2, upper_road_up, frame);   
        sprites.drawOverwrite((x*8) - road.x, roadElements[x].lowerLimit, lower_road_up, frame);   
        break;
       
      case RoadType::Down:
        sprites.drawOverwrite((x*8) - road.x, roadElements[x].upperLimit, upper_road_down, frame);   
        sprites.drawOverwrite((x*8) - road.x, roadElements[x].lowerLimit - 2, lower_road_down, frame);   
        break;
        
    }

  }

  road.x+=scrollIncrement;
  delay(10);
  
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
