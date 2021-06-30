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
	if (x % 10 <= 4) {
	if (y % 10 <= 4) {
		return HSLAPixel(310, .87, .33, 1);
	} else {
		return HSLAPixel(208, .87, .27, 1);
	}
	} else {
	if (y % 10 > 5) {
		return HSLAPixel(52, .87, .47, 1);
	} else {
		return HSLAPixel(81, .87, .60, 1);
	}
	} 

}
