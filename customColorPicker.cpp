#include "customColorPicker.h"

customColorPicker::customColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
    color = fillColor;
    im = img; 
    tol = tolerance;
    ctr = center;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
    HSLAPixel black;
    black.l = 1.0;  
    return black; 
}
