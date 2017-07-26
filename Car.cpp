#include "Car.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"

Car::Car(uint8_t name, Arduboy2 &arduboy, int16_t x, int16_t y, int16_t speed, const uint8_t *bitmapRef, const uint8_t *maskRef, const Car *cars, const SteeringType steeringType) {

  _name = name;
  _renderRequired = true;
  _x = x;
  _y = y;
  _enabled = false;
  _speed = speed;
  _arduboy = arduboy;
  _bitmap = bitmapRef;
  _mask = maskRef;
  _cars = cars;
  _steeringType = steeringType;

}

bool Car::operator==(const Car& rhs)const {
  return (this->getName() == rhs.getName());
}

bool Car::operator!=(const Car& rhs)const {
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
 *  Get rectangle of image.
 */
Rect Car::getRect() {

  return (Rect){this->getX(), this->getY(), pgm_read_byte(_bitmap), pgm_read_byte(_bitmap[1])};

}

/*
 *  Get rectangle of image.
 */
Rect Car::getRect(int16_t x, int16_t y) {

  return (Rect){(x / 10), (y / 10), pgm_read_byte(_bitmap), pgm_read_byte(_bitmap[1])};

}

/*
 *  Simply scrolling the images to the left does not force the image to be rendered again.
 */
void Car::move(uint8_t pixels, uint8_t roadUpper, uint8_t roadLower) {
//Serial.print("Scroll - Car_");
//Serial.println(this->getName());

  bool noCollisions = true;

  int16_t x = _x - (pixels * 10) - _speed;
  int16_t y = _y;

  switch (_steeringType) {

    case (SteeringType::FollowRoad):

      if (_roadUpper > 0 && _roadLower > 0) {

        y = y + (_roadUpper - roadUpper);
        _roadUpper = roadUpper;
        _roadLower = roadLower;
        
      }

      break;

    case (SteeringType::ZigZag):

      if (_goingUp) {

        if (_y > roadUpper) {
          --y;        
        }
        else {
          _goingUp = !_goingUp;
        }
        
      }
      else {
        
        if (_y < roadLower) {
          ++y;        
        }
        else {
          _goingUp = !_goingUp;
        }
        
      }
      
      break;

    case (SteeringType::Random):
 /*
    road.randomCount--;
    
    if (road.randomCount == 0) {
      
      if (road.randomNumber > 0) {
        road.randomNumber = 0;
      }
      else {
        road.randomNumber = random((uint8_t)RoadType::First, (uint8_t)RoadType::Count);   
      }

      road.randomCount = random(2, 6);
      
    }
*/
      break;
      
  }

  for (uint8_t i = 0; i < 3; ++i) {

    const Car &car = _cars[i];
    car.debug();

    if (car != *this) {
    
      if (_arduboy.collide(car.getRect(), this->getRect(_x, _y))) {

        this->debug();
        noCollisions = false;
        break;

      }

    }

  }

  // No collision occured with this 
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

const int16_t Car::getX() {

  return _x / 10;

}

void Car::setX(const int16_t value) {

  _x = value * 10;
  _renderRequired = true;

}

const int16_t Car::getY() {

  return _y / 10;

}

void Car::setY(const int16_t value) {

  _y = value * 10;
  _renderRequired = true;

}


const int16_t Car::getSpeed() {

  return _speed;

}

void Car::setSpeed(const int16_t value) {

  _speed = value;
  _renderRequired = true;

}


const bool Car::getEnabled() {

  return _enabled;

}


void Car::setEnabled(const bool value) {

  _enabled = value;
  _renderRequired = true;

}



const bool Car::getRenderRequired() {

  return _renderRequired;

}


void Car::setRenderRequired(const bool value) {

  _renderRequired = value;

}

int Car::getWidth() {

  return pgm_read_byte(_bitmap);

}

int16_t Car::getHeight() {

  return pgm_read_byte(_bitmap[1]);

}

/*void Car::setSprites(const Sprites *value) {

  _sprites = value;

}*/
/*
void Car::setArduboy(Arduboy2 &value) {

  _arduboy = value;

}
*/
/*
void Car::setCars(const Car *value) {

  _cars = value;

}
*/
const byte Car::getName() {

  return _name;

}


void Car::setBitmap(const uint8_t *value) {

  _bitmap = value;
  
}

void Car::setMask(const uint8_t *value) {

  _mask = value;
  
}

void Car::renderImage(int16_t frame) {
  
  
Serial.print("renderImage - Car_");
Serial.print(this->getName());
Serial.print(", renderRequired:");
Serial.print(this->getRenderRequired());
Serial.print(", enabled:");
Serial.print(this->getEnabled());
Serial.println("");

  if (_renderRequired && _enabled) {

    Sprites::drawExternalMask(this->getX(), this->getY(), _bitmap, _mask, frame, frame);
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
    Sprites::drawErase(this->getX(), this->getY(), _bitmap, frame);
    _renderRequired = true;
  }
  
}
