/**
loose functions for vision, not belonging to a class
 */

#ifndef _VISION_H_
#define _VISION_H_

using namespace std;

//uses the image to find the pixel coordinates of the base of a cylinder (or line)
PixelPoint findObject(Cylinder cyl);

//converts the pixel coordinates to a real-life relative position
PolarPoint placeObject(PixelPoint);



#endif
