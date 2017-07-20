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

#define BUFFER_ROW_0_END      BUFFER_ROW_0_START + WIDTH - 1
#define BUFFER_ROW_1_END      BUFFER_ROW_1_START + WIDTH - 1
#define BUFFER_ROW_2_END      BUFFER_ROW_2_START + WIDTH - 1
#define BUFFER_ROW_3_END      BUFFER_ROW_3_START + WIDTH - 1
#define BUFFER_ROW_4_END      BUFFER_ROW_4_START + WIDTH - 1
#define BUFFER_ROW_5_END      BUFFER_ROW_5_START + WIDTH - 1
#define BUFFER_ROW_6_END      BUFFER_ROW_6_START + WIDTH - 1
#define BUFFER_ROW_7_END      BUFFER_ROW_7_START + WIDTH - 1

byte upperLimit[WIDTH];
byte lowerLimit[WIDTH];


const int scrollIncrement = 2;
int frame = 0;
int x = 0;
bool dirUp = false;

Car car1;
Car car2;
Car car3;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
    // (positions start at 0, 0)
  arduboy.setCursor(4, 9);

  // then we print to screen what is in the Quotation marks ""
  arduboy.print(F("Hello, world!"));
  arduboy.print(WIDTH);
  arduboy.sBuffer[1]=255;
arduboy.sBuffer[24]=255;
arduboy.sBuffer[25]=255;
arduboy.sBuffer[127]=255;

car1.setX(115);
car1.setY(32);
car1.bitmap = car;
car1.setEnabled(true);
car1.renderImage(sprites, frame);

car2.setX(128);
car2.setY(48);
car2.bitmap = car;
car2.setEnabled(true);
car2.setSpeed(-10);
car2.renderImage(sprites, frame);

car3.setX(128);
car3.setY(16);
car3.bitmap = car;
car3.setEnabled(true);
//car3.setSpeed(-6);
car3.renderImage(sprites, frame);
    arduboy.display();
}


void loop() {
  // pause render until it's time for the next frame
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
  
  Serial.print("Car.x: ");
  Serial.print(car1.getX());
  Serial.print(", y:");
  Serial.print(car1.getY());
  Serial.print(", enabled:");
  Serial.print(car1.getEnabled());
  Serial.print(", renderRequired:");
  Serial.println(car1.getRenderRequired());
  
  
  car1.renderImage(sprites, frame);
  car2.renderImage(sprites, frame);
  car3.renderImage(sprites, frame);



  
  sprites.drawOverwrite(0, 24, car, frame);
  arduboy.drawPixel(127, x);

  if (dirUp == true) {
    x--; if (x< 0) { x = 0; dirUp = false; }
    
  }
  else {
    x++; if (x > 63) {x = 62; dirUp = true; }
  }
  
  
  arduboy.display();



}
