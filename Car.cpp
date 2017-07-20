#include "Car.h"
#include "Arduboy2.h"
#include "Sprites.h" 



Car::Car() {
	
  renderRequired = true;
  enabled = false;
  speed = 0;
  
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
 * Simply scrolling the images to the left does not force the image to be rendered again.
 */
void Car::scroll(byte pixels) {
	
	x = x - (pixels * 10) - speed;
  renderRequired = (speed != 0 || this->getX() > WIDTH - this->getWidth());
  enabled = (this->getWidth() + this->getX() > 0);
  
}

int Car::getX() {

	return x / 10;
	
}

void Car::setX(int value) {
  
  x = value * 10;
  renderRequired = true;
  
}

int Car::getY() {

  return y / 10;
	
}

void Car::setY(int value) {
	
  y = value * 10;
  renderRequired = true;
  
}


int Car::getSpeed() {

  return speed;
  
}

void Car::setSpeed(int value) {
  
  speed = value;
  renderRequired = true;
  
}


bool Car::getEnabled() {

  return enabled;
  
}


void Car::setEnabled(bool value) {
  
  enabled = value;
  renderRequired = true;
  
}



bool Car::getRenderRequired() {

  return renderRequired;
  
}


void Car::setRenderRequired(bool value) {
  
  renderRequired = value;
  
}

int Car::getWidth() {

	return pgm_read_byte(bitmap);
	
}

int Car::getHeight() {

	return pgm_read_byte(bitmap + 1);
	
}

void Car::renderImage(Sprites sprites, int16_t frame) {

  if (renderRequired && enabled) {
	  
    sprites.drawExternalMask(this->getX(), this->getY(), bitmap, mask, frame, frame);
    sprites.drawOverwrite(this->getX(), this->getY(), bitmap, frame);
	  
    renderRequired = false;
      
  }
}

