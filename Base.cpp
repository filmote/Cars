#include "Base.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"
#include "FixedPoints.h"
#include "FixedPointsCommon.h"

Base::Base(SQ15x16 x, SQ15x16 y, const uint8_t *bitmapRef, const uint8_t *maskRef) {

  _x = x;
  _newX = x;
  _y = y;
  _newY = y;
  _bitmap = bitmapRef;
  _mask = maskRef;

}


/*
 *  Get rectangle of image.
 */
Rect Base::getRect() const {

  return (Rect){this->getX().getInteger(), this->getY().getInteger(), pgm_read_byte(&_bitmap[0]), pgm_read_byte(&_bitmap[1])};

}

Rect Base::getNewRect() const {

  return (Rect){this->getNewX().getInteger(), this->getNewY().getInteger(), pgm_read_byte(&_bitmap[0]), pgm_read_byte(&_bitmap[1])};

}

/*
 *  Get rectangle of image.
 */
Rect Base::getRect(int16_t x, int16_t y) const {

  return (Rect){x, y, pgm_read_byte(_bitmap), pgm_read_byte(_bitmap[1])};

}

const SQ15x16 Base::getX() const {

  return _x;

}

void Base::setX(const SQ15x16 value) {

  _x = value;
  _newX = value;

}

const SQ15x16 Base::getY() const {

  return _y;

}

void Base::setY(const SQ15x16 value) {

  _y = value;
  _newY = value;

}

const SQ15x16 Base::getDeltaX() const {

  return _newX - _x;

}

const SQ15x16 Base::getDeltaY() const {

  return _newY - _y;

}

uint8_t Base::getWidth() const {

  return pgm_read_byte(&_bitmap[0]);

}

uint8_t Base::getHeight() const {

  return pgm_read_byte(&_bitmap[1]);

}


/*
const uint8_t Base::getBitmap() const {

  return _bitmap;
  
}*/
void Base::setBitmap(const uint8_t *value) {

  _bitmap = value;
  
}
/*
const uint8_t Base::getMask() const {

  return _mask;
  
}
*/
void Base::setMask(const uint8_t *value) {

  _mask = value;
  
}

void Base::renderImage(int16_t frame) {

  if (this->getX().getInteger() + this->getWidth() >= 0 && this->getX().getInteger() < WIDTH) {
    Sprites::drawExternalMask(this->getX().getInteger(), this->getY().getInteger(), _bitmap, _mask, frame, frame);
  }

  _newX = _x;
  _newY = _y;

}

void Base::clearImage(int16_t frame) {

  if (this->getX().getInteger() + this->getWidth() >= 0 && this->getX().getInteger() < WIDTH) {
    Sprites::drawErase(this->getX().getInteger(), this->getY().getInteger(), _bitmap, frame);
  }
  
}

void Base::updatePosition() {

  _x = _newX;
  _y = _newY;

}

const SQ15x16 Base::getNewX() const {

  return _newX;

}

void Base::setNewX(const SQ15x16 value) {

  _newX = value;

}

const SQ15x16 Base::getNewY() const {

  return _newY;

}

void Base::setNewY(const SQ15x16 value) {

  _newY = value;

}
