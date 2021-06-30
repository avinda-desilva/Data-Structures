#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
* Calculates a metric for the difference between two pixels, used to
* calculate if a pixel is within a tolerance.
*
* @param p1 First pixel
* @param p2 Second pixel
* @return the difference between two HSLAPixels
*/
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
* Default iterator constructor.
*/
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  png_ = PNG(0, 0);
  traversal_ = NULL;
  tolerance_ = 0;
  head_point_ = Point(0, 0);
  curr_point = head_point_;
  reachedEnd = false;
}

ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal* traversal) {
  /** @todo [Part 1] */
  png_ = png;
  head_point_ = start;
  curr_point = head_point_;
  tolerance_ = tolerance;
  reachedEnd = false;
  traversal_ = traversal;
  for (unsigned int x = 0; x < png.width(); x++) {
    for (unsigned int y = 0; y < png.height(); y++) {
      hasTraversed.push_back(false); //Initializes vector containing boolean if that point has been visited.
    }
  }
  if (!canTraverseTo(curr_point)) {
    reachedEnd = true;
  }
}

bool ImageTraversal::Iterator::canTraverseTo(const Point & point) {
  if (point.x >= png_.width() || point.y >= png_.height()) {return false;}
  HSLAPixel pixel1 = png_.getPixel(head_point_.x, head_point_.y);
  HSLAPixel pixel2 = png_.getPixel(point.x, point.y);
  if (hasTraversed[point.x + point.y * png_.width()]) {return false;}
  if (calculateDelta(pixel1, pixel2) < tolerance_) {
    hasTraversed[point.x + point.y * png_.width()] = true;
    return true;
  }
  return false;
}

/**
* Iterator increment opreator.
*
* Advances the traversal of the image.
*/
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  traversal_->add(Point(curr_point.x + 1, curr_point.y));
  traversal_->add(Point(curr_point.x, curr_point.y + 1));
  traversal_->add(Point(curr_point.x - 1, curr_point.y));
  traversal_->add(Point(curr_point.x, curr_point.y - 1));

  Point next = traversal_->pop();
  while(!canTraverseTo(next) && !(traversal_->empty())) {
    next = traversal_->pop();
  }
  if (traversal_->empty()) {
    reachedEnd = true;
    return *this;
  } else {
    curr_point = next;
    return *this;
  }
}




bool ImageTraversal::Iterator::getEnd() {
  return reachedEnd;
}

void ImageTraversal::Iterator::setEnd(bool end) {
  reachedEnd = end;
}

/**
* Iterator accessor opreator.
*
* Accesses the current Point in the ImageTraversal.
*/
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_point;
}

/**
* Iterator inequality operator.
*
* Determines if two iterators are not equal.
*/
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (reachedEnd != other.reachedEnd) {
    return true;
  } else {
    return false;
  }
}
