/*
* File:        priority.cpp
* Description: Implements a priority ordering structure specially made for determining the
*              order of neighbours visited in PA2's filler::fill function.
*              Note that this does NOT serve the same purpose as the stack/queue
*              ordering structure which you have also been asked to implement.
*
*              Ignoring resize costs, any single insertion or removal operation
*              should cost at most O(n), where n is the number of PixelPoints
*              stored in the collection.
*
* Date:        2022-02-10 02:04
*
*/

#include "priority.h"
#include <cmath>
#include <cstdlib>
#include <assert.h>

using namespace cs221util;
using namespace std;

/*
*  Default constructor
*  Initializes refcolor to the default color according to the HSLAPixel implementation.
*/
PriorityNeighbours::PriorityNeighbours() {
  // complete your implementation below
  refcolor = HSLAPixel();

}

/*
*  Parameterized constructor
*  Initializes refcolor to the supplied value.
*/
PriorityNeighbours::PriorityNeighbours(HSLAPixel ref) {
  // complete your implementation below
  refcolor = ref;
}

/*
*  Inserts an item into the collection
*  PARAM: p - item to be inserted
*  POST:  the collection contains p, along with all previously existing items.
*/
void PriorityNeighbours::Insert(PixelPoint p) {
  // complete your implementation below
  points.push_back(p);

}

/*
*  Removes and returns an item from the collection satisfying the priority condition
*  PRE:    the collection is not empty (but it would be good to check anyway!).
*  POST:   the item satisfying the priority condition is removed from the collection.
*  RETURN: the item satisfying the priority condition
*
*  Priority condition:
*    The PixelPoint in the collection whose color is the minimum distance away
*    from the reference color is the priority item to be returned.
*
*    In case of multiple items with the same priority value (i.e. minimal distance
*    away from the reference color), the one with the minimal y-coordinate will be
*    selected.
*    In case of multiple items with the same priority value and the same y-coordinate,
*    the one with the minimal x-coordinate will be selected.
*
*    ***ATTENTION*** The dist() function in HSLAPixel.h will be very helpful!
*
*  Combined with Insert(), think about the time complexity of maintaining the
*  priority order and/or accessing the priority element in this specific application!
*/
PixelPoint PriorityNeighbours::Remove() {
  // complete your implementation below
  
  int temp_num=-1;
  double temp_dist=999999;
  double rdist=refcolor.dist(refcolor);
  int size=points.size();
  for(int i=0;i<size;i++){
    if(abs(refcolor.dist(points[i].color)-rdist)<temp_dist){
      temp_num=i;
      temp_dist=abs(refcolor.dist(points[i].color)-rdist);
    }
    else if(abs(refcolor.dist(points[i].color)-rdist)==temp_dist){
      if(points[i].y<points[temp_num].y){
        temp_num=i;
      }
      else if(points[i].y==points[temp_num].y){
        if(points[i].x<points[temp_num].x){
          temp_num=i;
        }
      }
    }
  }
  PixelPoint temp_point=points[temp_num];

  points.erase(points.begin()+temp_num);


  return temp_point; // REPLACE THIS STUB
}

/*
*  Checks if the collection is empty
*  RETURN: true, if the collection is empty
*          false, otherwise
*/
bool PriorityNeighbours::IsEmpty() const {
  // complete your implementation below
  
  if(points.size() == 0){
    return true;
  }
  else{
    return false;
  }
  
}

/*
*  Returns the value of the reference color
*/
HSLAPixel PriorityNeighbours::GetReferenceColor() const {
  // complete your implementation below
  
  return refcolor;
}

/*
*  Sets the reference color attribute
*  POST: refcolor is set to the supplied value
*/
void PriorityNeighbours::SetReferenceColor(HSLAPixel ref) {
  // complete your implementation below
  
  refcolor = ref;
  
}