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
car1.renderImage(sprites, frame);
    arduboy.display();
}


void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame())) return;
  
  scrollBuffer(scrollIncrement);
  car1.renderImage(sprites, frame);
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
