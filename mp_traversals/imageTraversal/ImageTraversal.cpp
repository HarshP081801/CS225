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
  traversal_ = NULL;
  atEnd = false;
}
//custom iterator constructor 

ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal* traversal) {
  png_ = png;
  current_ = start;
  trueStart_ = current_;
  tolerance_ = tolerance;
  traversal_ = traversal;

  for (unsigned int i = 0; i < (png_.width() * png_.height()); i++) {
    alreadyVisited_.push_back(false);
  }
  atEnd = false;
  if (canVisit(current_)) {
    alreadyVisited_[current_.x + current_.y * png_.width()] = true;
    path_.push_back(current_);
  } else {
    atEnd = true;
  }

}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point p1 = Point(current_.x + 1, current_.y );
  Point p2 = Point(current_.x, current_.y + 1);
  Point p3 = Point(current_.x - 1, current_.y);
  Point p4 = Point(current_.x, current_.y - 1);

  if (canVisit(p1)) traversal_->add(p1);
  if (canVisit(p2)) traversal_->add(p2);
  if (canVisit(p3)) traversal_->add(p3);
  if (canVisit(p4)) traversal_->add(p4);

  if (traversal_->empty()) {
    setEnd(true);
    return *this;
  }
  Point next = traversal_->pop();
  while (alreadyVisited_[next.x + next.y * png_.width()]) {
    if (traversal_->empty()) {
      setEnd(true);
      return *this;
    }
    next = traversal_->pop();
  }
  current_ = next;
  alreadyVisited_[current_.x + current_.y * png_.width()] = true;
  path_.push_back(current_);
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool toReturn = (atEnd != other.atEnd);
  return toReturn;
}
//Private function setEnd

void ImageTraversal::Iterator::setEnd(bool end) {
  atEnd = end;
}
//Private function canVisit

bool ImageTraversal::Iterator::canVisit(Point point) {
  if (point.x >= png_.width() || point.y >= png_.height()) return false;

  HSLAPixel start = (png_.getPixel(trueStart_.x, trueStart_.y));
  HSLAPixel toCheck = (png_.getPixel(point.x, point.y));
  if (calculateDelta(start, toCheck) >= tolerance_) return false;

  return true;
}

