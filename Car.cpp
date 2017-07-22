#include "Car.h"
#include "Arduboy2.h"
#include "Sprites.h" 
#include "Arduino.h"

Car::Car(String name) {

  _name = name;
  _renderRequired = true;
  _enabled = false;
  _speed = 0;
  
}

bool Car::operator==(Car& rhs)const{
  return (this->getName()==rhs.getName());
}

bool Car::operator!=(Car& rhs)const{
  return (this->getName()!=rhs.getName());
}

void Car::debug() {
  
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
  Serial.print(", bitmap=");
  Serial.print(*bitmap);
  Serial.println(" ");
  
}


/*
 * Get rectangle of image.
 */
Rect Car::getRect() {
   
  return (Rect){this->getX(), this->getY(), pgm_read_byte(bitmap), pgm_read_byte(bitmap + 1)};

}


/*
 * Simply scrolling the images to the left does not force the image to be rendered again.
 */
void Car::scroll(byte pixels) {

  bool noCollisions = true;
  
  int x = _x - (pixels * 10) - _speed;
  int y = _y;

  for (int i = 0; i < 3; ++i) {

    Car car = _cars[i];

    if (car != *this) {

      if (_arduboy.collide(car.getRect(), this->getRect())) {
        
        Serial.println("- Collide ----------------------------");
        car.debug();
        this->debug();

      }
      
    }

  }

  if (noCollisions) {
    
  	_x = x;
    _y = y;
    _renderRequired = (_speed != 0 || this->getX() > WIDTH - this->getWidth());
    _enabled = (this->getWidth() + this->getX() > 0);
    
  }
  
}

int Car::getX() {

	return _x / 10;
	
}

void Car::setX(int value) {
  
  _x = value * 10;
  _renderRequired = true;
  
}

int Car::getY() {

  return _y / 10;
	
}

void Car::setY(int value) {
	
  _y = value * 10;
  _renderRequired = true;
  
}


int Car::getSpeed() {

  return _speed;
  
}

void Car::setSpeed(int value) {
  
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

int Car::getHeight() {

	return pgm_read_byte(bitmap + 1);
	
}

void Car::setSprites(Sprites value) {

  _sprites = value;
  
}

void Car::setArduboy(Arduboy2 value) {

  _arduboy = value;
  
}

void Car::setCars(Car value[]) {

  _cars = value;
  
}

String Car::getName() {

  return _name;
  
}
void Car::renderImage(int16_t frame) {

  if (_renderRequired && _enabled) {
	  
    _sprites.drawExternalMask(this->getX(), this->getY(), bitmap, mask, frame, frame);
    _sprites.drawOverwrite(this->getX(), this->getY(), bitmap, frame);
	  
    _renderRequired = false;
      
  }
  
}

