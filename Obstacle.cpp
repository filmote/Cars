#include "Obstacle.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"

Obstacle::Obstacle(SQ7x8 x, SQ7x8 y, const uint8_t *bitmapRef, const uint8_t *maskRef) :
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

void Obstacle::renderImage(int16_t frame) {

  if (this->getEnabled() && this->getX().GetInteger() + this->getWidth() >= 0 && this->getX().GetInteger() < WIDTH) {
    Sprites::drawExternalMask(this->getX().GetInteger(), this->getY().GetInteger(), _bitmap, _mask, frame, frame);
  }
  else if (this->getX().GetInteger() + this->getWidth() < 0) {
    this->setEnabled(false);
  }

}
