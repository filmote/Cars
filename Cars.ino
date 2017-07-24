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

#define NUMBER_OF_CAR_IMAGES  1
#define NUMBER_OF_CARS        3
const int scrollIncrement = 2;
int frame = 0;

enum class RoadType {
  Straight,
  Up,  
  Down
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
}
road = { 0, -16, 68, RoadType::Straight, 0, 2 };

struct Player {
  byte x;
  byte y;
  const byte height;
  const byte width;
}
player = {0, 24, 14, 16};


Car car1 = Car(1);
Car car2 = Car(2);
Car car3 = Car(3);

const byte* car_images[] = { car_01,     car_02,     car_03,     car_04,     car_05,     car_06,     car_07,     car_08 };
const byte* car_masks[] =  { mask_20_12, mask_19_12, mask_16_10, mask_19_12, mask_18_10, mask_17_13, mask_17_14, mask_19_15 };
Car* cars[] = { &car1, &car2, &car3 };

void setup() {
  
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
  
  car1.setSprites(&sprites);
  car1.setArduboy(&arduboy);
  car1.setCars(cars);
  car1.setX(80);
  car1.setY(48);
  car1.bitmap = car_images[7];
  car1.mask = car_masks[7];
  car1.setSpeed(-4);
  car1.setEnabled(true);
  car1.renderImage(frame);
  
  car2.setSprites(&sprites);
  car2.setArduboy(&arduboy);
  car2.setCars(cars);
  car2.setX(128);
  car2.setY(32);
  car2.bitmap = car_images[4];
  car2.mask = car_masks[4];
  car2.setEnabled(true);
  car2.setSpeed(-10);
  car2.renderImage(frame);
  
  car3.setSprites(&sprites);
  car3.setArduboy(&arduboy);
  car3.setCars(cars);
  car3.setX(128);
  car3.setY(16);
  car3.bitmap = car_03;
  car3.mask = mask_16_10;
  car3.setSpeed(-8);
  car3.setEnabled(true);
  car3.renderImage(frame);

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
  car1.clearImage(frame);
  car2.clearImage(frame);
  car3.clearImage(frame);

  if (arduboy.pressed(UP_BUTTON) && player.y > 0)                           { player.y--; }
  if (arduboy.pressed(DOWN_BUTTON) && player.y < HEIGHT - player.height)    { player.y++; }
  if (arduboy.pressed(LEFT_BUTTON) && player.x > 0)                         { player.x--; }
  if (arduboy.pressed(RIGHT_BUTTON) && player.x < 64)                       { player.x++; }
 
  scrollBuffer(scrollIncrement);

  drawScenery();
  
  car1.scroll(scrollIncrement);
  car2.scroll(scrollIncrement);
  car3.scroll(scrollIncrement);

  if (!car1.getEnabled()) { 
    car1.setX(WIDTH);
    car1.setEnabled(true);
  }

  if (!car2.getEnabled()) {  
    car2.setX(WIDTH);
    car2.setEnabled(true);
  }
  
  if (!car3.getEnabled()) {  
    car3.setX(WIDTH);
    car3.setEnabled(true);
  }
  
  car1.renderImage(frame);
  car2.renderImage(frame);
  car3.renderImage(frame);
  
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
        road.randomNumber = random(0,3);
      }

      road.randomCount = random(4,8);
      
    }

    road.x = 0;

    switch (road.randomNumber) {
      
      case (int)RoadType::Straight:
        break;
        
      case (int)RoadType::Up:
        if (road.y > -20) {
          road.y-=2;
          road.type = RoadType::Up;
        }
        break;
        
      case (int)RoadType::Down:
        if (road.y < -8) {   // height = 64, -4 height = 72, -4 height = 68, -8
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

