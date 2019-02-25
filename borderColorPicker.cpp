#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
    color = fillColor;
    im = img; 
    tol = tolerance;
    ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{
    HSLAPixel *original = im.getPixel(x,y);
    //create vector of pixels that are distance 3 away from x and y
    vector<HSLAPixel> pixelsWithinThree; 
    for(int xi = -2; xi < 4; xi++){
        //cout<<"\n\nxi: "<<xi<<endl;
        for(int yi = -2; yi < 4; yi++){
            int newX = x + xi; 
            int newY = y + yi;
            if(newX > 0 && newX < im.width() && newY > 0 && newY < im.height()){
                if(xi != 0 || yi != 0){
                    HSLAPixel *p = im.getPixel(newX,newY);
                        bool same = ctr == *p;
                    if(p->dist(ctr) > tol){
                        return color; 
                    }
                } 
            }else{
                return color;
            }
        }
    }

    return *original; 
}
