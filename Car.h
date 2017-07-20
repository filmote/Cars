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
     
     int16_t getX();
     void setX(int16_t x);
     int16_t getY();
     void setY(int16_t y);
     
     int16_t getWidth();
     int16_t getHeight();

     const uint8_t *bitmap;
     const uint8_t *mask;
     
   private:
        boolean renderRequired;
     int16_t x;
     int16_t y;
};
#endif
