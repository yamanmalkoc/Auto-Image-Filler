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
    if(inBorder(x,y))
        return color;
        
    HSLAPixel *original = im.getPixel(x,y);
    for(int xi = -2; xi < 3; xi++){
        for(int yi = -2; yi < 3; yi++){
            int newX = x + xi; 
            int newY = y + yi;
            if(changeColor(newX,newY)){
                return color; 
            }
        }
    }

    //check the last four outside pixels 
    /*
                    o
                0 0 0 0 0  
                0 0 0 0 0  
              o 0 0 0 0 0 o
                0 0 0 0 0  
                0 0 0 0 0
                    o      
    */
   int incre = 3;
   int newX = x;
   int newY = y - incre;
   if(changeColor(newX,newY)){
        return color; 
   }

   newY = y + incre;
   if(changeColor(newX,newY)){
        return color; 
   }

   newX = x + incre;
   newY = y;
   if(changeColor(newX,newY)){
       return color; 
   }

   newX = x - incre;
   if(changeColor(newX,newY)){
       return color; 
   } 
    return *original; 
}

bool borderColorPicker::inBorder(int x, int y){
    int w = im.width();
    int h = im.height();
    bool top = y >= 0 && y < 3;
    bool bottom = y < h && y > h-4;
    bool right = x < w && x > w-4;
    bool left = x >= 0 && x < 3;
    return top || bottom || right || left; 
}

bool borderColorPicker::inFrame(int x, int y){
    int w = im.width();
    int h = im.height();
    bool top = y >= 0;
    bool bottom = y < h;
    bool right = x < w;
    bool left = x >= 0;
    return top && bottom && right && left; 
}

 bool borderColorPicker::changeColor(int x, int y){

    if(!inFrame(x,y)) return true; 

    HSLAPixel *p = im.getPixel(x,y);
    if(p->dist(ctr) > tol) return true; 
    
    return false; 
 }
