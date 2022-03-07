/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  // complete your implementation below
  img = inputimg;
  
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below
  HSLAPixel *pixel = img.getPixel(p.x, p.y);
  
  pixel->l = 1-pixel->l;
  if(pixel->h+180>360){
    pixel->h = pixel->h-180;
  }
  else{
    pixel->h = 180+pixel->h;
  }
  

  return *pixel; // REPLACE THIS STUB
}
