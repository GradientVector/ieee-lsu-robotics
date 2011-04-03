/**
loose functions for vision, not belonging to a class
 */

#ifndef _VISION_H_
#define _VISION_H_

using namespace std;

//finds a line on the screen
//returns the center of the line segment found. If the line on the screen goes from (300,10) to (200,50), the return value will be (250,30).  
PixelPoint findLine();

//uses the image to find the pixel coordinates of the base of a cylinder (or line)
PixelPoint findObject(Cylinder cyl);

//converts the pixel coordinates to a real-life relative position
PolarPoint placeObject(PixelPoint);



#endif
