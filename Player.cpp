#include "Player.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"

Player::Player(SQ7x8 x, SQ7x8 y, const uint8_t *bitmapRef, const uint8_t *maskRef) :
        Base(x, y, bitmapRef, maskRef) {

}
