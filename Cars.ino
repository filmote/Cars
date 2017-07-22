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

byte upperLimit[WIDTH];
byte lowerLimit[WIDTH];

const int scrollIncrement = 2;
int frame = 0;
int x = 0;
bool dirUp = false;

Car car1 = Car("Car_01");
Car car2 = Car("Car_02");
Car car3 = Car("Car_03");

const byte* car_images[] = { car_01 };
const Car cars[] = { car1, car2, car3 };

void setup() {
  
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.setCursor(4, 9);
  
  car1.setSprites(sprites);
  car1.setArduboy(arduboy);
  car1.setCars(cars);
  car1.setX(80);
  car1.setY(32);
  car1.bitmap = car_01;
  car1.setEnabled(true);
  car1.renderImage(frame);
  
  car2.setSprites(sprites);
  car2.setArduboy(arduboy);
  car2.setCars(cars);
  car2.setX(128);
  car2.setY(32);
  car2.bitmap = car_01;
  car2.setEnabled(true);
  car2.setSpeed(-10);
  car2.renderImage(frame);
  
  car3.setSprites(sprites);
  car3.setArduboy(arduboy);
  car3.setCars(cars);
  car3.setX(128);
  car3.setY(16);
  car3.bitmap = car_01;
  car3.setEnabled(true);
  car3.renderImage(frame);

  arduboy.display();

}


void loop() {
  
  if (!(arduboy.nextFrame())) return;

  scrollBuffer(scrollIncrement);
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
  
  sprites.drawOverwrite(0, 24, car_01, frame);
  arduboy.drawPixel(127, x);

  if (dirUp == true) {
    x--; if (x< 0) { x = 0; dirUp = false; }
    
  }
  else {
    x++; if (x > 63) {x = 62; dirUp = true; }
  }
  
  
  arduboy.display();

}
