#include "customColorPicker.h"

customColorPicker::customColorPicker(HSLAPixel fillColor, PNG & img, int radius,HSLAPixel center)
{
    color = fillColor;
    im = img; 
    rad = radius;
    ctr = center;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
    HSLAPixel *curr = im.getPixel(x,y); 
    double dist = getDistance(x,y); 
    // cout<<"dist: "<<(int)dist<<endl;
    // cout<<"rad: "<<rad<<endl; 
    // cout<<"\n\n";
    if((int)dist % rad == 0){
        return color; 
    }
    return *curr; 
}

double customColorPicker::getDistance(int x, int y){
    int midx = im.width()/2; 
    int midy = im.height()/2; 
    return sqrt(pow((x-midx),2) + pow((y-midy),2)); 
}




