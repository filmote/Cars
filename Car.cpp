#include "Car.h"
#include "Arduboy2.h"
#include "Sprites.h"
#include "Enums.h"

uint8_t randomCount = 0;
uint8_t randomNumber = 0;
        
int16_t _roadUpper;
int16_t _roadLower;       
bool _goingUp;
    
Car::Car(uint8_t name, SQ7x8 x, SQ7x8 y, SQ7x8 speedX, const uint8_t *bitmapRef, const uint8_t *maskRef, const Car *cars, const SteeringType steeringType) :
     Base(x, y, bitmapRef, maskRef) {

  _name = name;
  _speedX = speedX;
  _enabled = false;
  _cars = cars;
  _steeringType = steeringType;

}

bool Car::operator==(const Car& rhs) const {
  return (this->getName() == rhs.getName());
}

bool Car::operator!=(const Car& rhs) const {
  return (this->getName() != rhs.getName());
}


void Car::calcNewPosition(uint8_t pixels, int16_t roadUpper, int16_t roadLower) {

  SQ7x8 x = this->getX() - pixels - this->getSpeedX();
  SQ7x8 y = this->getY();

  if (x >= 0) {  // No steering for cars leaving screen ..
    
    switch (_steeringType) {
  
      case (SteeringType::FollowRoad):
  
        if (_roadUpper > 0 && _roadLower > 0) {
  
          if (_roadUpper > roadUpper) {      // Road is going up.
            y = y - 2;
          }
          else if (_roadUpper < roadUpper) {      // Road is going down.
            y = y + 2;
          }
          
        }
  
        break;
  
      case (SteeringType::ZigZag):

        if (_goingUp) {
  
          if (y.GetInteger() > roadUpper) {
            y = y - _speedY;        
          }
          else {
            _goingUp = !_goingUp;
          }
          
        }
        else {
          if (y.GetInteger() + (this->getHeight()) < roadLower) {
            y = y + _speedY;        
          }
          else {
            _goingUp = !_goingUp;
          }
          
        }
        
        break;
  
      case (SteeringType::Random):
 
        randomCount--;
        
        if (randomCount == 0) {
          
          if (randomNumber > 0) {
            randomNumber = 0;
          }
          else {
            randomNumber = random((uint8_t)RoadType::First, (uint8_t)RoadType::Count);   
          }
    
          randomCount = random(15, 30);
          
        }
        
        switch ((RoadType)randomNumber) {
          
          case RoadType::Straight:
            break;
            
          case RoadType::Up:
//Serial.println("Up");
            if (y > roadUpper) {
              y = y - _speedY;
            }
            break;
            
          case RoadType::Down:
//Serial.println("Down");
            if (y < roadLower) {
              y = y + _speedY;
            }
            break;
            
        }
        
        break;
        
    }
    
  }

  this->setNewX(x);
  this->setNewY(y);

}



/*
 *  Simply scrolling the images to the left does not force the image to be rendered again.
 * /
void Car::move(uint8_t pixels, int16_t roadUpper, int16_t roadLower) {

  if (this->getEnabled()) {

    bool noCollisions_XY = true;
    bool noCollisions_X = true;
    bool noCollisions_Y = true;
  
    SQ7x8 x = this->getX() - pixels - this->getSpeedX();
    SQ7x8 y = this->getY();

    if (x >= 0) {  // No steering for cars leaving screen ..
      
      switch (_steeringType) {
    
        case (SteeringType::FollowRoad):
    
          if (_roadUpper > 0 && _roadLower > 0) {
    
            if (_roadUpper > roadUpper) {      // Road is going up.
              y = y - 2;
            }
            else if (_roadUpper < roadUpper) {      // Road is going down.
              y = y + 2;
            }
            
          }
    
          break;
    
        case (SteeringType::ZigZag):

          if (_goingUp) {
    
            if (y.GetInteger() > roadUpper) {
              y = y - _speedY;        
            }
            else {
              _goingUp = !_goingUp;
            }
            
          }
          else {
            if (y.GetInteger() + (this->getHeight()) < roadLower) {
              y = y + _speedY;        
            }
            else {
              _goingUp = !_goingUp;
            }
            
          }
          
          break;
    
        case (SteeringType::Random):
   
          randomCount--;
          
          if (randomCount == 0) {
            
            if (randomNumber > 0) {
              randomNumber = 0;
            }
            else {
              randomNumber = random((uint8_t)RoadType::First, (uint8_t)RoadType::Count);   
            }
      
            randomCount = random(15, 30);
            
          }
          
          switch ((RoadType)randomNumber) {
            
            case RoadType::Straight:
              break;
              
            case RoadType::Up:
//Serial.println("Up");
              if (y > roadUpper) {
                y = y - _speedY;
              }
              break;
              
            case RoadType::Down:
//Serial.println("Down");
              if (y < roadLower) {
                y = y + _speedY;
              }
              break;
              
          }
          
          break;
          
      }
      
    }
    
    for (uint8_t i = 0; i < 3; ++i) {
  
      const Car &car = _cars[i];
 //     car.debug();
  
      if (car != *this && car.getEnabled()) {

        
        if (collide(car.getRect(), this->getRect(x.GetInteger(), y.GetInteger()))) {

          noCollisions_XY = false;
          

          if (collide(car.getRect(), this->getRect(x.GetInteger(), this->getY().GetInteger()))) {

            noCollisions_X = false;
            
          }

          else if (collide(car.getRect(), this->getRect(this->getX().GetInteger(), y.GetInteger()))) {

            noCollisions_Y = false;

          }
  
//          this->debug();
          break;
  
        }
  
      }
  
    }

    // No collision occured with this 
    if (noCollisions_XY) {
//Serial.println("noCollisions_XY");      

      this->setX(x); 
      this->setY(y); 
  
    }
    else {
      
      if (noCollisions_X) { 
//Serial.println("noCollisions_X");      
        this->setX(x); 
      }
      else  if (noCollisions_Y) { 
//Serial.println("noCollisions_Y");      
        this->setY(y); 
      }
      else {
        this->setX(this->getX() - this->getSpeedX()); 
      }
      

    }

    _roadUpper = roadUpper;
    _roadLower = roadLower;
  
//  Serial.print("this->getWidth(): ");
//  Serial.print(this->getWidth());
//  Serial.print(", this->getX(): ");
//  Serial.print(this->getX().GetInteger());
//  Serial.print(", enabled: ");
//  Serial.print(_enabled);
    _enabled = (this->getWidth() + this->getX().GetInteger() > 0);
//  Serial.print(", ");
//  Serial.println(_enabled);

//    if (!_enabled) {
//      Serial.print(F("Car_"));
//      Serial.print(this->getName());
//      Serial.println(F(" enabled = false"));
//    }

  }
  
}

*/

const bool Car::getEnabled() const {

  return _enabled;

}

void Car::setEnabled(const bool value) {

  _enabled = value;

}

const byte Car::getName() const {

  return _name;

}

const SteeringType Car::getSteeringType() const {

  return _steeringType;

}

void Car::setSteeringType(const SteeringType value) {

  _steeringType = value;
  
}

const SQ7x8 Car::getSpeedX() const {

  return _speedX;

}

void Car::setSpeedX(const SQ7x8 value) {

 _speedX = value;

}

const SQ7x8 Car::getSpeedY() const {

  return _speedY;

}

void Car::setSpeedY(const SQ7x8 value) {

 _speedY = value;

}


void Car::renderImage(int16_t frame) {

  if (this->getEnabled() && this->getX().GetInteger() + this->getWidth() >= 0 && this->getX().GetInteger() < WIDTH) {
    Sprites::drawExternalMask(this->getX().GetInteger(), this->getY().GetInteger(), _bitmap, _mask, frame, frame);
  }

}

void Car::clearImage(int16_t frame) {

  if (this->getEnabled() && this->getX().GetInteger() + this->getWidth() >= 0 && this->getX().GetInteger() < WIDTH) {
    Sprites::drawErase(this->getX().GetInteger(), this->getY().GetInteger(), _bitmap, frame);
  }
  
}

bool Car::collide(Rect rect1, Rect rect2) const {
  
  return !(rect2.x                >= rect1.x + rect1.width  ||
           rect2.x + rect2.width  <= rect1.x                ||
           rect2.y                >= rect1.y + rect1.height ||
           rect2.y + rect2.height <= rect1.y);
}

