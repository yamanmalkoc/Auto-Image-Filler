#include "stripeColorPicker.h"

stripeColorPicker::stripeColorPicker(HSLAPixel fillColor, int stripeSpacing)
{
    color = fillColor; 
    spacing = stripeSpacing;  
}

/**
 * Picks the color for pixel (x, y). If the x or y coordinate is a
 * multiple of the spacing, it will be filled with the fillColor.
 * otherwise, it will be filled with white.
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinat to pick a color for.
 * @return The color chosen for (x, y).
 */
HSLAPixel stripeColorPicker::operator()(int x, int y)
{
    if(x % spacing == 0){
        return color; 
    }

    HSLAPixel ret; 
    // ret.l = 1.0;
    return ret; 
}
