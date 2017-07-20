#ifndef CAR_H
#define CAR_H
 
#include "Arduboy2.h"
#include "Sprites.h"

class Car {

   public:
	   Car();
     Rect getOuterRect();
     Rect getInnerRect();
     void renderImage(Sprites sprite, int16_t frame);
     void scroll(byte pixels);
     
     int getX();
     int getY();
     int getSpeed();
     bool getEnabled();
     bool getRenderRequired();

     void setX(int value);
     void setY(int value);
     void setSpeed(int value);
     void setEnabled(bool value);
     void setRenderRequired(bool value);
     
     int16_t getWidth();
     int16_t getHeight();

     const uint8_t *bitmap;
     const uint8_t *mask;
     
   private:
     bool renderRequired;
     int x;               // factor of 10
     int y;               // factor of 10
     int speed;           // factor of 10
     bool enabled;
};
#endif
