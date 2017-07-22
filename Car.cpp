#include "Car.h"
#include "Arduboy2.h"
#include "Sprites.h" 

Car::Car(Sprites sprites) {

  _sprites = sprites;
  _renderRequired = true;
  _enabled = false;
  _speed = 0;
  
}


/*
 * Get rectangle of image.
 * 
 * Assumption is the image is surrounded by a single pixel space on four sides
 */
Rect Car::getOuterRect() {
   
  return (Rect){this->getX(), this->getY(), pgm_read_byte(bitmap), pgm_read_byte(bitmap + 1)};

}

/*
 * Get rectangle surrounding the car itself.
 * 
 * Assumption is the image is surrounded by a single pixel space on four sides
 */
Rect Car::getInnerRect() {
   
  return (Rect){this->getX() + 1, this->getY() + 1, pgm_read_byte(bitmap) - 2, pgm_read_byte(bitmap + 1) - 2};

}

/*
 * Get rectangle surrounding the car itself.
 * 
 * Assumption is the image is surrounded by a single pixel space on four sides
 *
Rect getInnerRect(int x, int y) {
   
  return (Rect){x, y, pgm_read_byte(bitmap) - 2, pgm_read_byte(bitmap + 1) - 2};

}
*/
/*
 * Simply scrolling the images to the left does not force the image to be rendered again.
 */
void Car::scroll(byte pixels) {

  bool noCollisions = true;
  
  int x = _x - (pixels * 10) - _speed;
  int y = _y;

  int size = sizeof(cars) / sizeof(Car);

  for(int i = 0; i < 3; ++i) {
    //
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

void Car::renderImage(int16_t frame) {

  if (_renderRequired && _enabled) {
	  
    _sprites.drawExternalMask(this->getX(), this->getY(), bitmap, mask, frame, frame);
    _sprites.drawOverwrite(this->getX(), this->getY(), bitmap, frame);
	  
    _renderRequired = false;
      
  }
  
}

