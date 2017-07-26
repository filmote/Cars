#ifndef CAR_H
#define CAR_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"

class Car {

   public:
	   Car(uint8_t name, Arduboy2 &arduboy, int16_t x, int16_t y, int16_t speed, const uint8_t *bitmapRef, const uint8_t *maskRef, const Car *cars);
     bool operator==(const Car &rhs)const; 
     bool operator!=(const Car &rhs)const; 

     void debug();

     Rect getRect();
     Rect getRect(int x, int y);
     void renderImage(int16_t frame);
     void clearImage(int16_t frame);
     void scroll(byte pixels);
     
     const int16_t getX();
     const int16_t getY();
     const int16_t getSpeed();
     const bool getEnabled();
     const bool getRenderRequired();
     const byte getName();

     void setX(const int value);
     void setY(const int value);
     void setSpeed(const int value);
     void setEnabled(const bool value);
     void setRenderRequired(const bool value);
//     void setSprites(const Sprites *value);
//     void setArduboy(Arduboy2 &value);
     void setCars(const Car *value);

     int16_t getWidth();
     int16_t getHeight();

     const uint8_t *bitmap;
     const uint8_t *mask;
     
   private:
     bool _renderRequired;
     int16_t _x;               // factor of 10
     int16_t _y;               // factor of 10
     int16_t _speed;           // factor of 10
     bool _enabled;
     uint8_t _name;
//     const Sprites *_sprites;
     Arduboy2 &_arduboy;
     const Car *_cars;

};
#endif
