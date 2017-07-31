#ifndef PLAYER_H
#define PLAYER_H
 
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"
#include "Enums.h"
#include "Base.h"


class Player : public Base {
  
   public:
   
     Player(SQ7x8 x, SQ7x8 y, const uint8_t *bitmapRef, const uint8_t *maskRef);

};
#endif
