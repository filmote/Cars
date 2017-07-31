#include "Player.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"

#define SCALING_FACTOR 10

Player::Player(SQ7x8 x, SQ7x8 y, const uint8_t *bitmapRef, const uint8_t *maskRef) :
        Base(x, y, bitmapRef, maskRef) {

}
