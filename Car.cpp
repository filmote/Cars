#include "Car.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Arduino.h"

Car::Car(uint8_t name) {

  _name = name;
  _renderRequired = true;
  _enabled = false;
  _speed = 0;

}

bool Car::operator==(Car& rhs)const {
  return (this->getName() == rhs.getName());
}

bool Car::operator!=(Car& rhs)const {
  return (this->getName() != rhs.getName());
}

void Car::debug() {

  Serial.print("Car_");
  Serial.print(this->getName());
  Serial.print(": x=");
  Serial.print(this->getX());
  Serial.print(", y=");
  Serial.print(this->getY());
  Serial.print(", width=");
  Serial.print(this->getWidth());
  Serial.print(", height=");
  Serial.print(this->getHeight());
  Serial.print(", xMax=");
  Serial.print(this->getX() + this->getWidth());
  Serial.print(", yMax=");
  Serial.print(this->getY() + this->getHeight());
  Serial.print(", rect=");
  Serial.print(this->getRect().x);
  Serial.print(" ");
  Serial.print(this->getRect().y);
  Serial.print(" ");
  Serial.print(this->getRect().width);
  Serial.print(" ");
  Serial.print(this->getRect().height);
  Serial.println(" ");

}


/*
   Get rectangle of image.
*/
Rect Car::getRect() {

  return (Rect){this->getX(), this->getY(), pgm_read_byte(bitmap), pgm_read_byte(bitmap + 1)};

}

/*
   Get rectangle of image.
*/
Rect Car::getRect(int x, int y) {

  return (Rect){(x / 10), (y / 10), pgm_read_byte(bitmap), pgm_read_byte(bitmap + 1)};

}

/*
   Simply scrolling the images to the left does not force the image to be rendered again.
*/
void Car::scroll(byte pixels) {
//Serial.print("Scroll - Car_");
//Serial.println(this->getName());

  bool noCollisions = true;

  int16_t x = _x - (pixels * 10) - _speed;
  int16_t y = _y;

  for (int i = 0; i < 3; i++) {

    const Car &car = _cars[i];

    if (car != *this) {
    
      if (_arduboy.collide(car.getRect(), this->getRect(_x, _y))) {

        car.debug();
        this->debug();
        noCollisions = false;
        break;

      }

    }

  }

  if (noCollisions) {

    _x = x;
    _y = y;
    _renderRequired = (_speed != 0 || this->getX() >= WIDTH - this->getWidth());

  }
  else {

    _x = _x - (pixels * 10);
    _renderRequired = (this->getX() >= WIDTH - this->getWidth());
    
  }

  _enabled = (this->getWidth() + this->getX() > 0);
  if (!_enabled) {
    Serial.print("Car_");
    Serial.print(this->getName());
    Serial.println(" enabled = false");
  }
}

int16_t Car::getX() {

  return _x / 10;

}

void Car::setX(int16_t value) {

  _x = value * 10;
  _renderRequired = true;

}

int16_t Car::getY() {

  return _y / 10;

}

void Car::setY(int value) {

  _y = value * 10;
  _renderRequired = true;

}


int16_t Car::getSpeed() {

  return _speed;

}

void Car::setSpeed(int16_t value) {

  _speed = value;
  _renderRequired = true;

}


bool Car::getEnabled() {

  return _enabled;

}


void Car::setEnabled(bool value) {

  _enabled = value;
  _renderRequired = true;

}



bool Car::getRenderRequired() {

  return _renderRequired;

}


void Car::setRenderRequired(bool value) {

  _renderRequired = value;

}

int Car::getWidth() {

  return pgm_read_byte(bitmap);

}

int16_t Car::getHeight() {

  return pgm_read_byte(bitmap + 1);

}

/*void Car::setSprites(const Sprites *value) {

  _sprites = value;

}*/

void Car::setArduboy(Arduboy2 &value) {

  _arduboy = value;

}

void Car::setCars(const Car *value) {

  _cars = value;

}

byte Car::getName() {

  return _name;

}

void Car::renderImage(int16_t frame) {
/* 
Serial.print("renderImage - Car_");
Serial.print(this->getName());
Serial.print(", renderRequired:");
Serial.print(this->getRenderRequired());
Serial.print(", enabled:");
Serial.print(this->getEnabled());
Serial.println("");
*/
  if (_renderRequired && _enabled) {

    Sprites::drawExternalMask(this->getX(), this->getY(), bitmap, mask, frame, frame);
    _renderRequired = false;

  }

}

void Car::clearImage(int16_t frame) {
/* 
Serial.print("renderImage - Car_");
Serial.print(this->getName());
Serial.print(", renderRequired:");
Serial.print(this->getRenderRequired());
Serial.print(", enabled:");
Serial.print(this->getEnabled());
Serial.println("");
*/
  if (_speed != 0) {
    Sprites::drawErase(this->getX(), this->getY(), bitmap, frame);
    _renderRequired = true;
  }
  
}
