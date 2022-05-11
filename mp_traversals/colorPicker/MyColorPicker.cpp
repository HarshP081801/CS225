#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  if (num == 0) {
    if (swap) {
      hue = 0;
      swap = false;
      num = 1;
    } else {
      hue = 90;
      swap = true;
    }
  } else {
    if (swap) {
      hue = 180;
      swap = false;
      num = 0;
    } else {
      hue = 270;
      swap = true;
    }
  }
  HSLAPixel pixel(hue, .5, .5);
  return pixel;
}
