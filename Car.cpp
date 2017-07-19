#include "Car.h"
#include "Arduboy2.h"
#include "Sprites.h"



Car::Car() {
	
  renderRequired = true;
  
}


/*
 * Get rectangle of image.
 * 
 * Assumption is the image is surrounded by a single pixel space on four sides
 */
Rect Car::getOuterRect() {
   
  return (Rect){x, y, pgm_read_byte(bitmap), pgm_read_byte(bitmap + 1)};

}

/*
 * Get rectangle surrounding the car itself.
 * 
 * Assumption is the image is surrounded by a single pixel space on four sides
 */
Rect Car::getInnerRect() {
   
  return (Rect){x + 1, y + 1, pgm_read_byte(bitmap) - 2, pgm_read_byte(bitmap + 1) - 2};

}


/*
 * Simply scrolling the images to the left does not force the image to be rendered again.
 */
void Car::scroll(byte pixels) {
	
	y = y - pixels;
	
}

int16_t Car::getX() {

	return x;
	
}

void Car::setX(int16_t x) {
  
  x = x;
  renderRequired = true;
  
}

int16_t Car::getY() {

  return y;
	
}

void Car::setY(int16_t y1) {
	
  y = y1;
  renderRequired = true;
  
}

int16_t Car::getWidth() {

	return pgm_read_byte(bitmap);
	
}

int16_t Car::getHeight() {

	return pgm_read_byte(bitmap + 1);
	
}

void Car::renderImage(Sprites sprites, int16_t frame) {
Serial1.println("renderImage");
  if (x <= WIDTH && renderRequired) {
	  
//    sprites.drawExternalMask(x, y, bitmap, mask, frame, frame);
    sprites.drawOverwrite(x, y, bitmap, frame);
	  renderRequired = false;
	  
  }
	
}

