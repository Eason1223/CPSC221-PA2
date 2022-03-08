/*
*  File: censorColorPicker.cpp
*  Implements the censor color picker for CPSC 221 PA2.
*
*/

#include "censorColorPicker.h"

#include <math.h> // gives access to sqrt function

/*
*  Useful function for computing the Euclidean distance between two PixelPoints
*/
double PointDistance(PixelPoint a, PixelPoint b) {
  unsigned int diff_x, diff_y;
  if (a.x > b.x)
    diff_x = a.x - b.x;
  else
    diff_x = b.x - a.x;
  if (a.y > b.y)
    diff_y = a.y - b.y;
  else
    diff_y = b.y - a.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

CensorColorPicker::CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG& iputimage)
{
  // complete your implementation below
  PNG inputimage=iputimage;
  img = inputimage;
  blockwidth=b_width;
  radius=rad;


  double count=b_width*b_width;

  for (unsigned x = 0; x < inputimage.width(); x=x+b_width) {//make mosaic image img
    for (unsigned y = 0; y < inputimage.height(); y=y+b_width) {//every mosaic block


      double h_sum=0;
      double s_sum=0;
      double l_sum=0;
      double a_sum=0;

      for (unsigned i = x; i < x+b_width; i++) {
        for (unsigned h = y; h < y+b_width; h++) {
          HSLAPixel *inpixel = inputimage.getPixel(i, h);
          h_sum= h_sum+inpixel->h;
          s_sum= s_sum+inpixel->s;
          l_sum= l_sum+inpixel->l;
          a_sum= a_sum+inpixel->a;

        }
      }

      double h_aver=h_sum/count;
      double s_aver=s_sum/count;
      double l_aver=l_sum/count;
      double a_aver=a_sum/count;

      for (unsigned i = x; i < x+b_width; i++) {
        for (unsigned h = y; h < y+b_width; h++) {
          HSLAPixel *outpixel = img.getPixel(i, h);
          outpixel->h=h_aver;
          outpixel->s=s_aver;
          outpixel->l=l_aver;
          outpixel->a=a_aver;

        }
      }


    }
  }

  for (unsigned x = 0; x < inputimage.width(); x++) {
    for (unsigned y = 0; y < inputimage.height(); y++) {
      PixelPoint point = PixelPoint(x, y, *inputimage.getPixel(x, y));
      if( PointDistance(point,ctr)<=rad){
        HSLAPixel *outpixel = img.getPixel(x, y);
        HSLAPixel *inpixel = inputimage.getPixel(x, y);
        inpixel->h=outpixel->h;
        inpixel->s=outpixel->s;
        inpixel->l=outpixel->l;
        inpixel->a=outpixel->a;
      }
    }
  }

  img=inputimage;

  
}

HSLAPixel CensorColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below
  HSLAPixel *pixel = img.getPixel(p.x, p.y);
  return *pixel; // REPLACE THIS STUB
}
