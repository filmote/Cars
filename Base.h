#ifndef BASE_H
#define BASE_H
 
#include "Sprites.h"
#include "Enums.h"
#include "Enums.h"
#include "FixedPoints.h"
#include "FixedPointsCommon.h"

class Base {

   public:

     Base(SQ15x16 x, SQ15x16 y, const uint8_t *bitmapRef, const uint8_t *maskRef);

     Rect getRect() const;
     Rect getRect(int x, int y) const;
     Rect getNewRect() const;

     void renderImage(int16_t frame);
     void clearImage(int16_t frame);
     void updatePosition();
     
     const SQ15x16 getX() const;
     const SQ15x16 getY() const;
     const SQ15x16 getNewX() const;
     const SQ15x16 getNewY() const;
     const SQ15x16 getDeltaX() const;
     const SQ15x16 getDeltaY() const;

     void setX(const SQ15x16 value);
     void setY(const SQ15x16 value);
     void setNewX(const SQ15x16 value);
     void setNewY(const SQ15x16 value);
     void setBitmap(const uint8_t *value);
     void setMask(const uint8_t *value);

     uint8_t getWidth() const;
     uint8_t getHeight() const;
     
   private:
     SQ15x16 _x;               
     SQ15x16 _y;               
     SQ15x16 _newX;            
     SQ15x16 _newY;            

   protected:
     const uint8_t *_bitmap;
     const uint8_t *_mask;
};
#endif
