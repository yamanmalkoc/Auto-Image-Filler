/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
#include "filler.h"

animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    stripeColorPicker a(fillColor,stripeSpacing);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    //get the centre pixel of the image
    HSLAPixel *cen = img.getPixel(x,y);
    borderColorPicker a(borderColor,img,tolerance,*cen);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

/* Given implementation of a DFS rainbow fill. */
animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    stripeColorPicker a(fillColor,stripeSpacing);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
     //get the centre pixel of the image
    int width = img.width(); 
    int height = img.height(); 
    HSLAPixel *cen = img.getPixel(width/2,height/2);
    borderColorPicker a(borderColor,img,tolerance,*cen);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

/* Given implementation of a BFS rainbow fill. */
animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

/*
Method to obtain a point. Speed up process of examining neighbores. 
*/
vector<int> filler::createPoint(int x, int y){
    vector<int> point;
    point.push_back(x);
    point.push_back(y);
    return point; 
}

/*
Method to check if a point has been processed already or not, and if it is within the tolerance. 
*/
bool filler::isValidToProcess(PNG& img, vector<int> point,HSLAPixel *centreP, vector<vector<bool>> markedPoints, double tolerance){
    //check if the point has been processed.
    int x = point.at(0);
    int y = point.at(1);
    //check if the x and y are in the correct range
    if(x < 0 || x >= img.width() || y < 0 || y >= img.height()){
        return false;
    }
    if(markedPoints.at(x).at(y) == 1){
        return false; 
    }
    HSLAPixel *pointP = img.getPixel(x,y); 
    if(pointP->dist(*centreP) > tolerance){
        return false; 
    } 
    return true; 
}


template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    int count = 0; //To keep track of how many pixels are being added to the animation

    animation a;    //The animation that will be returned. 

    //Create the structure to hold information on pixels having been marked or not
    //Based on their x and y 
    int cols = img.width();
    int rows = img.height();

    vector< vector< bool > > marked( cols, vector<bool>( rows, false ) );

    //Create an ordering structure
    OrderingStructure<vector<int>> os; 

    HSLAPixel *centre = img.getPixel(x,y);

    HSLAPixel original;
    original = original = *centre; //create a copy of the centre pixel before I process it and change the colour. 

    *centre = fillColor(x,y); 
    vector<int> centrePoint; 
    centrePoint.push_back(x);
    centrePoint.push_back(y);
    marked.at(x).at(y) = 1; //Set the point as marked. 
    os.add(centrePoint);
    count++; 
    if(count%frameFreq==0){
        a.addFrame(img);
    }

    while(os.isEmpty()==0){

        vector<int> next = os.remove();
        vector<vector<int>> neighbores; 
        int currX = next[0];
        int currY = next[1];
        /*
        UPRIGHT(+x,-y), UP(-y), UPLEFT(-x,-y), LEFT(-x), 
        DOWNLEFT(-x,+y), DOWN(+y), DOWNRIGHT(+x,+y), RIGHT(+x)**
        */
        neighbores.push_back(createPoint(currX+1,currY-1)); //upright
        neighbores.push_back(createPoint(currX,currY-1));   //up
        neighbores.push_back(createPoint(currX-1,currY-1)); //upleft
        neighbores.push_back(createPoint(currX-1,currY));   //left
        neighbores.push_back(createPoint(currX-1,currY+1)); //downleft
        neighbores.push_back(createPoint(currX,currY+1));   //down
        neighbores.push_back(createPoint(currX+1,currY+1)); //downright
        neighbores.push_back(createPoint(currX+1,currY));   //right
        //for each neighbore we check if it has been marked and if the distance from the main one is within tolerance. 
        for(vector<int> n : neighbores){ 
            if(isValidToProcess(img,n,&original,marked,tolerance)){
                int xP = n.at(0);
                int yP = n.at(1); 
                HSLAPixel *nPixel = img.getPixel(xP,yP);
                *nPixel = fillColor(xP,yP); 
                marked.at(xP).at(yP) = 1; //Set the point as marked
                os.add(n); 
                count++; 
                if(count%frameFreq==0){
                    a.addFrame(img);
                }
            }
        }    
    }     
    a.addFrame(img);
    return a; 

    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure. 
     *
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are within
     *              (or equal to) tolerance distance from the center, to the 
     *              ordering structure.
     *        2.    use the colorPicker to set the new color of the neighbors
     *        3.    mark the neighbors as processed.
     *        4.    as you process a neighbor, if it is an appropriate frame, 
     *              send the current PNG to the animation (as described below)."
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 8 neighbors, consisting of 
     *        the 8 pixels who share an edge or corner with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the ordering structure (queue or stack) 
     *        is as follows: **UPRIGHT(+x,-y), UP(-y), UPLEFT(-x,-y), LEFT(-x), 
     *        DOWNLEFT(-x,+y), DOWN(+y), DOWNRIGHT(+x,+y), RIGHT(+x)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.  
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */



} 
