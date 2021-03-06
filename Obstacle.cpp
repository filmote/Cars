#include "Obstacle.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"

Obstacle::Obstacle(SQ15x16 x, SQ15x16 y, const uint8_t *bitmapRef, const uint8_t *maskRef) :
          Base(x, y, bitmapRef, maskRef) {

  _enabled = false;
  
}

void Obstacle::move(uint8_t pixels) {

  this->setX(this->getX() - pixels);

}

const bool Obstacle::getEnabled() const {

  return _enabled;

}

void Obstacle::setEnabled(const bool value) {

  _enabled = value;

}

const ObstacleType Obstacle::getObstacleType() const {

  return _obstacleType;

}

void Obstacle::setObstacleType(const ObstacleType value) {

  _obstacleType = value;
  
}

void Obstacle::renderImage(int16_t frame) {

  if (this->getEnabled() && this->getX().getInteger() + this->getWidth() >= 0 && this->getX().getInteger() < WIDTH) {
    Sprites::drawExternalMask(this->getX().getInteger(), this->getY().getInteger(), _bitmap, _mask, frame, frame);
  }
  else if (this->getX().getInteger() + this->getWidth() < 0) {
    this->setEnabled(false);
  }

}
