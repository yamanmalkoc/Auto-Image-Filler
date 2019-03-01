/**
 * @file customColorPicker.h
 * Definition of a border color picker.
 *
 */
#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"
#include <cmath>

/**
 * borderColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate. If the given position is near a border of 
 * the fill, then it should be colored with the given color. Otherwise, its color
 * should not change.
 *
 * The following criteria should be used to determine if a position p is near
 * a border: if p is within distance 3 of any cell that will be outside the 
 * fill, then the pixel at position p should be colored with the given color.
 *
 * You will use Euclidian distance to judge proximity. That means if p is at 
 * location (x,y), its distance to a point at location (a,b) is 
 * squareRoot([(x-a)^2 + (y-b)^2]). Note that you should not ever have to 
 * compute the square root to solve this problem.
 *
 **/
class customColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new borderColorPicker.
     *
     * @param fillColor Color for the border .
     * @param tolerance used to determine the border of the fill.
     * @param center the color used to determine whether or not a point is within
     *          the fill region. 
     */

    customColorPicker(HSLAPixel fillColor, PNG & img, int radius,HSLAPixel center);

    /**
     * Picks the color for pixel (x, y). If the x or y coordinate is 
     * near the border of the fill, or the border of the image, 
     * the fillColor will be returned.
     * Otherwise, the current color of (x,y) will be returned.
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

    double getDistance(int x, int y);

  private:
    HSLAPixel color; /**< Color used for the grid border. */
    PNG im;
    int rad;
    HSLAPixel ctr;
};

#endif