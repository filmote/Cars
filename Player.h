#ifndef PLAYER_H
#define PLAYER_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"
#include "Enums.h"
#include "Base.h"


class Player : public Base {
  
  public:
   
    Player(SQ15x16 x, SQ15x16 y, SQ15x16 fuel, const uint8_t *bitmapRef, const uint8_t *maskRef);
    
    const SQ15x16 getFuel() const;
    const uint16_t getScore() const;

    void setFuel(const SQ15x16 value);
    void setScore(const uint16_t value);
  
  private:
    uint16_t _score;
    SQ15x16 _fuel;
    
};
#endif
