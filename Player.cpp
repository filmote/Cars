#include "Player.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"

Player::Player(SQ7x8 x, SQ7x8 y, SQ7x8 fuel, const uint8_t *bitmapRef, const uint8_t *maskRef) :
        Base(x, y, bitmapRef, maskRef) {
          
  _fuel = fuel;

}

const SQ7x8 Player::getFuel() const {

  return _fuel;

}

void Player::setFuel(const SQ7x8 value) {

  _fuel = value;

}

const uint16_t Player::getScore() const {

  return _score;

}

void Player::setScore(const uint16_t value) {

  _score = value;

}

