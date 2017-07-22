#ifndef CAR_H
#define CAR_H
 
#include "Arduboy2.h"
#include "Sprites.h"

class Car {

   public:
	   Car(Sprites sprites);
     Rect getOuterRect();
     Rect getInnerRect();
     void renderImage(int16_t frame);
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
     const Car* cars[];
     
   private:
     bool _renderRequired;
     int _x;               // factor of 10
     int _y;               // factor of 10
     int _speed;           // factor of 10
     bool _enabled;
     Sprites _sprites;
};
#endif
