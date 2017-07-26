#ifndef CAR_H
#define CAR_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"
#include "Enums.h"


class Car {

   public:
	 Car(uint8_t name, Arduboy2 &arduboy, int16_t x, int16_t y, int16_t speed, const uint8_t *bitmapRef, const uint8_t *maskRef, const Car *cars, const SteeringType steeringType);
     bool operator==(const Car &rhs) const; 
     bool operator!=(const Car &rhs) const; 

     void debug() const;

     Rect getRect() const;
     Rect getRect(int x, int y) const;
     void renderImage(int16_t frame);
     void clearImage(int16_t frame);
     void move(uint8_t pixels, uint8_t roadUpper, uint8_t roadLower);
     
     const int16_t getX() const;
     const int16_t getY() const;
     const int16_t getSpeed() const;
     const bool getEnabled() const;
     const bool getRenderRequired() const;
     const byte getName() const;

     void setX(const int16_t value);
     void setY(const int16_t value);
     void setSpeed(const int16_t value);
     void setEnabled(const bool value);
     void setRenderRequired(const bool value);
//     void setSprites(const Sprites *value);
//     void setArduboy(Arduboy2 &value);
     void setBitmap(const uint8_t *value);
     void setMask(const uint8_t *value);

     int16_t getWidth() const;
     int16_t getHeight() const;
     
   private:
     bool _renderRequired;
     int16_t _x;               // factor of 10
     int16_t _y;               // factor of 10
     int16_t _speed;           // factor of 10
     bool _enabled;
     uint8_t _name;
//     const Sprites *_sprites;
     Arduboy2 *_arduboy;
     const Car *_cars;

     const uint8_t *_bitmap;
     const uint8_t *_mask;
     SteeringType _steeringType;

     // Steering details ..
     bool _goingUp;          // direction
     uint8_t _roadUpper;
     uint8_t _roadLower;
};
#endif
