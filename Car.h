#ifndef CAR_H
#define CAR_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"
#include "Enums.h"
#include "Base.h"


class Car : public Base {

  public:  
    Car(uint8_t name, SQ15x16 x, SQ15x16 y, SQ15x16 speedX, const uint8_t *bitmapRef, const uint8_t *maskRef, const Car *cars, const SteeringType steeringType);
    
    bool operator==(const Car &c) const; 
    bool operator!=(const Car &c) const; 

        
    void debug() const;
    
    void calcNewPosition(uint8_t pixels, int16_t roadUpper, int16_t roadLower); 
    void renderImage(int16_t frame);
    void clearImage(int16_t frame);
       
    const uint8_t getName() const;
    const bool getEnabled() const;
    const SQ15x16 getSpeedX() const;
    const SQ15x16 getSpeedY() const;
    const SteeringType getSteeringType() const;
    const int16_t getRoadUpper() const;
    const int16_t getRoadLower() const;
    
    void setName(const uint8_t value);
    void setEnabled(const bool value);
    void setSpeedX(const SQ15x16 value);
    void setSpeedY(const SQ15x16 value);
    void setSteeringType(const SteeringType value);
    void setRoadUpper(const int16_t value);
    void setRoadLower(const int16_t value);
  
  private:
    bool _enabled;
    uint8_t _name;
    const Car *_cars;
    SteeringType _steeringType;
    SQ15x16 _speedX;      
    SQ15x16 _speedY;  


    // Steering variables ..
    
    uint8_t randomCount = 0;
    uint8_t randomNumber = 0;
    int16_t _roadUpper;
    int16_t _roadLower;       
    bool _goingUp;

};
#endif
