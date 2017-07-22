#ifndef CAR_H
#define CAR_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"

class Car {

   public:
	   Car(String name);
     bool operator==(Car &rhs)const; 
     bool operator!=(Car &rhs)const; 

     void debug();

     Rect getRect();
     void renderImage(int16_t frame);
     void scroll(byte pixels);
     
     int getX();
     int getY();
     int getSpeed();
     bool getEnabled();
     bool getRenderRequired();
     String getName();

     void setX(int value);
     void setY(int value);
     void setSpeed(int value);
     void setEnabled(bool value);
     void setRenderRequired(bool value);
     void setSprites(Sprites value);
     void setArduboy(Arduboy2 value);
     void setCars(Car* value);

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
     String _name;
     Sprites _sprites;
     Arduboy2 _arduboy;
     Car* _cars;

};
#endif
