#include "Player.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"

Player::Player(SQ15x16 x, SQ15x16 y, SQ15x16 fuel, const uint8_t *bitmapRef, const uint8_t *maskRef) :
        Base(x, y, bitmapRef, maskRef) {
          
  _fuel = fuel;

}

const SQ15x16 Player::getFuel() const {

  return _fuel;

}

void Player::setFuel(const SQ15x16 value) {

  _fuel = value;

}

const uint16_t Player::getScore() const {

  return _score;

}

void Player::setScore(const uint16_t value) {

  _score = value;

}

