#ifndef BASE_H
#define BASE_H
 
#include "Sprites.h"
#include "Enums.h"
#include "Enums.h"
#include "FixedPoints.h"
#include "FixedPointsCommon.h"

class Base {

   public:

     Base(SQ7x8 x, SQ7x8 y, const uint8_t *bitmapRef, const uint8_t *maskRef);

     Rect getRect() const;
     Rect getRect(int x, int y) const;
     Rect getNewRect() const;

     void renderImage(int16_t frame);
     void clearImage(int16_t frame);
     void updatePosition();
     
     const SQ7x8 getX() const;
     const SQ7x8 getY() const;
     const SQ7x8 getNewX() const;
     const SQ7x8 getNewY() const;
     const SQ7x8 getDeltaX() const;
     const SQ7x8 getDeltaY() const;

     void setX(const SQ7x8 value);
     void setY(const SQ7x8 value);
     void setNewX(const SQ7x8 value);
     void setNewY(const SQ7x8 value);
     void setBitmap(const uint8_t *value);
     void setMask(const uint8_t *value);

     uint8_t getWidth() const;
     uint8_t getHeight() const;
     
   private:
     SQ7x8 _x;               
     SQ7x8 _y;               
     SQ7x8 _newX;            
     SQ7x8 _newY;            

   protected:
     const uint8_t *_bitmap;
     const uint8_t *_mask;
};
#endif
