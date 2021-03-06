#ifndef OBSTACLE_H
#define OBSTACLE_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"
#include "Enums.h"
#include "Base.h"


class Obstacle : public Base {
  
  public:
   
    Obstacle(SQ15x16 x, SQ15x16 y, const uint8_t *bitmapRef, const uint8_t *maskRef);
    const bool getEnabled() const;
    const ObstacleType getObstacleType() const;
    
    void setEnabled(const bool value);
    void setObstacleType(const ObstacleType value);
         
    void move(uint8_t pixels);
    void renderImage(int16_t frame);  
    
  private:
    bool _enabled;
    ObstacleType _obstacleType;
     
};
#endif
