#ifndef PLAYER_H
#define PLAYER_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"
#include "Enums.h"
#include "Base.h"


class Player : public Base {
  
  public:
   
    Player(SQ7x8 x, SQ7x8 y, SQ7x8 fuel, const uint8_t *bitmapRef, const uint8_t *maskRef);
    
    const SQ7x8 getFuel() const;
    const uint16_t getScore() const;

    void setFuel(const SQ7x8 value);
    void setScore(const uint16_t value);
  
  private:
    uint16_t _score;
    SQ7x8 _fuel;
    
};
#endif
