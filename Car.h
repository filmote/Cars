#ifndef CAR_H
#define CAR_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"

class Car {

   public:
	   Car(uint8_t name);
     bool operator==(const Car &rhs)const; 
     bool operator!=(const Car &rhs)const; 

     void debug();

     Rect getRect();
     Rect getRect(int x, int y);
     void renderImage(int16_t frame);
     void clearImage(int16_t frame);
     void scroll(byte pixels);
     
     int16_t getX();
     int16_t getY();
     int16_t getSpeed();
     bool getEnabled();
     bool getRenderRequired();
     byte getName();

     void setX(int value);
     void setY(int value);
     void setSpeed(int value);
     void setEnabled(bool value);
     void setRenderRequired(bool value);
//     void setSprites(const Sprites *value);
     void setArduboy(Arduboy2 &value);
     void setCars(const Car *value);

     int16_t getWidth();
     int16_t getHeight();

     const uint8_t *bitmap;
     const uint8_t *mask;
     
   private:
     bool _renderRequired;
     int _x;               // factor of 10
     int _y;               // factor of 10
     int _speed;           // factor of 10
     bool _enabled;
     byte _name;
//     const Sprites* _sprites;
     Arduboy2 &_arduboy;
     const Car* _cars;

};
#endif
