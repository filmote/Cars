#include <Arduboy2.h>
#include "Car.h"
Arduboy2 arduboy;
Sprites sprites;

#define BUFFER_ROW_0_START    0
#define BUFFER_ROW_0_END  BUFFER_ROW_0_START + WIDTH - 1
#define BUFFER_ROW_1_START    BUFFER_ROW_0_START + WIDTH
#define BUFFER_ROW_1_END  BUFFER_ROW_1_START + WIDTH - 1
#define BUFFER_ROW_2_START    BUFFER_ROW_1_START + WIDTH
#define BUFFER_ROW_2_END  BUFFER_ROW_2_START + WIDTH - 1
#define BUFFER_ROW_3_START    BUFFER_ROW_2_START + WIDTH
#define BUFFER_ROW_3_END  BUFFER_ROW_3_START + WIDTH - 1
#define BUFFER_ROW_4_START    BUFFER_ROW_3_START + WIDTH
#define BUFFER_ROW_4_END  BUFFER_ROW_4_START + WIDTH - 1
#define BUFFER_ROW_5_START    BUFFER_ROW_4_START + WIDTH
#define BUFFER_ROW_5_END  BUFFER_ROW_5_START + WIDTH - 1
#define BUFFER_ROW_6_START    BUFFER_ROW_5_START + WIDTH
#define BUFFER_ROW_6_END  BUFFER_ROW_6_START + WIDTH - 1
#define BUFFER_ROW_7_START    BUFFER_ROW_6_START + WIDTH
#define BUFFER_ROW_7_END  BUFFER_ROW_7_START + WIDTH - 1

const byte PROGMEM car[] = {
  20, 16,
0x7F, 0xD5, 0x3F, 0x02, 0x9E, 0xA2, 0xBF, 0x31, 0x91, 0x31, 0xB7, 0xB1, 0x2E, 0x9E, 0x82, 0x86, 0x02, 0x3E, 0x04, 0xFC,
0x00, 0x03, 0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x06, 0x06, 0x06, 0x03,


};

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
  if (!(arduboy.nextFrame()))
    return;
    int f = arduboy.sBuffer + BUFFER_ROW_0_START + scrollIncrement;
Serial.print("WIDTH: ");
Serial.println(WIDTH);
Serial.print("  arduboy.sBuffer: ");
Serial.println((int)arduboy.sBuffer);
//Serial.print("  arduboy.sBuffer + BUFFER_ROW_0_START + scrollIncrement ");
//Serial.println(f);
//Serial.print("  WIDTH - scrollIncrement ");
//Serial.println(WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_0_START, arduboy.sBuffer + BUFFER_ROW_0_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_1_START, arduboy.sBuffer + BUFFER_ROW_1_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_2_START, arduboy.sBuffer + BUFFER_ROW_2_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_3_START, arduboy.sBuffer + BUFFER_ROW_3_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_4_START, arduboy.sBuffer + BUFFER_ROW_4_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_5_START, arduboy.sBuffer + BUFFER_ROW_5_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_6_START, arduboy.sBuffer + BUFFER_ROW_6_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_7_START, arduboy.sBuffer + BUFFER_ROW_7_START + scrollIncrement, WIDTH - scrollIncrement);

f= arduboy.sBuffer + WIDTH - scrollIncrement;
Serial.print("  arduboy.sBuffer + WIDTH - scrollIncrement ");
Serial.println(f);
Serial.print("  BUFFER_ROW_0_END - scrollIncrement ");
Serial.println(BUFFER_ROW_0_END - scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_0_END - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_1_END - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_2_END - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_3_END - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_4_END - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_5_END - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_6_END - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_7_END - scrollIncrement, 0, scrollIncrement);

  f= arduboy.sBuffer + BUFFER_ROW_0_END - scrollIncrement;
  arduboy.sBuffer[f] = 1;
  arduboy.sBuffer[f + 1] = 128;
/*
  arduboy.sBuffer[BUFFER_ROW_0_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_1_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_2_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_3_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_4_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_5_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_6_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_7_END] = 0;
*/
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
