/**
loose vision functions not belonging to any particular class
 */

#ifndef _VISION_CPP_
#define _VISION_CPP_
#include <math.h>
#include "vision.h"
#include "../nav/navigation.h"

#define PI 3.14159265

using namespace std; // #TODO: Remove this line - shouldn't define namespace in library file, only in actual executable.

Angle::Angle(){
    angle = 0;
}

Angle::Angle(double in_angle){
    angle = in_angle % 360;
}

double Angle::getAngle() {
	return angle;
}

void Angle::setAngle(double newAngle) {
	angle = newAngle % 360;
}


PixelPoint::PixelPoint()
{
  x = 0;
  y = 0;
  return 0;
}

PolarPoint placeObject(PixelPoint object) {

    double middle_x = Bot.IMG_WIDTH_PX/2;     // Coordinate for middle pixel on x axis
    double middle_y = IMG_HEIGHT_PX/2;    // Coordinate for middle pixel on y axis
    double diff_x;                        // Horizontal difference between camera middle pixel and object pixel
    double diff_y;                        // Vertical difference between camera middle pixel and object pixel
    Angle vertDiffAngle;                // Angle between middle of screen and vertical position of object, + = left of middle
    Angle horizDiffAngle;               // Angle between middle of screen and horizontal position of object, + = above middle
    Angle absVertAngle;                 // Object's angle relative to camera position on robot  #TODO: Rename variable
    double  distanceFromRobot;          // Distance between robot and object

    // find angle between robot's direction and object
    diff_x = (middle_x - object.x)/ middle_x;  // +middle_x = far left, -middle_x = far right
    horizDiffAngle.setAngle(diff_x * (HORIZ_FIELD_ANGLE/2));
   
    // calculate distance between robot and object
    diff_y = (middle_y - object.y)/middle_y;  // +middle_y = top, -middle_y = bottom
    vertDiffAngle.setAngle(diff_y * (VERT_FIELD_ANGLE/2));
    absVertAngle.setAngle(vertDiffAngle.getAngle() + VERTICAL_TILT_ANGLE);
    distanceFromRobot = fabs(CAMERA_HEIGHT * tan(absVertAngle.getAngle()*(PI/180)));  // based on trig function, same units as CAMERA_HEIGHT
    // #TODO: See if this works or if tan() needs to just be Math.tan()

    PolarPoint updated_position(distanceFromRobot , horizDiffAngle);
    
    return updated_position;
}



//this returns a color at a point
int color(Mat img, int x, int y) {
	//TODO by John West
	int& temp = img.at<uchar>(y, x);
	return temp;
}

PixelPoint findObject(cyl) {
    int clrLmt = 225; //color intensity minimum
    Mat gryClr = grayImage.getGI(cyl.color);
    PixelPoint cylPt(0, 0);
    for(int i = 1; i <= viewWidth; i++)
    {
	if (i <= viewHeight)
	{
	    for (int j = i; j <= viewHeight; j++)
	        if (color(gryClr, i - j, viewHeight - i + j) >= clrLmt)
		    if (checkArea(i - j, viewHeight - i + j, gryClr, cylPt))
		        return cylPt;
	}
	else
	{
	    for (int j = 1; j <= viewHeight; j++)
		if (color(gryClr, i - viewHeight + j, j) >= clrLmt)
		    if (checkArea(i - viewHeight + j, j, gryClr, cylPt))
			return cylPt;
	}
    }
    for (int i = viewHeight; i >= 1; i--)
	for (int j = i; j >= 1; j--)
	    if (color(gryClr, i - j, j) >= clrLmt)
		if (checkArea(i - j, j, gryClr, cylPt))
		    return cylPt;
    return cylPt;
}

bool checkArea(int cx, int cy, Mat gry, Point &Pt)//checks the average number of pixels of the same color
{
    int clrLmt = 225;
    int total = 0;
    int cap = 65; //predicted average as a percentage, change by experimentation
    int clr = 0; //amount of pixels with this color
    int topB, bottomB, leftB, rightB, LB, RB;
    for (int yy = cy - camScale*cy*(cylHeight + 5); yy <= cy + 5; yy++)
	for (int xx = cx - 5; xx <= cx + camScale*cy*(cylWidth + 5); x++)
	    if (color(gry, xx, yy) >= 225)
	    {
		total++;
		clr++;
	    }
    if ((total * 100) / clr >= cap) //finds the center pixel and adds it to the list of objects, may require a top cap ~90
    {
	for (int yy = cy - camScale*cy*(cylHeight + 5); !bottomB && yy <= cy; yy++)
	    for (int xx = cx; xx <= !bottomB && cx + camScale*cylWidth*cy; x++)
		if (color(gry, xx, yy) >= clrLmt)
		    bottomB = yy;
	for (int xx = cx - 5; !leftB && xx <= cx + camScale*cylWidth*cy; xx++)
	    for (int yy = cy - camScale*cy*cylHeight; !leftB && yy <= cy; yy++)
		if (color(gry, xx, yy) >= clrLmt)
		    leftB = xx;
	for (int xx = cx + camScale*cy*(cylWidth + 5); !rightB && xx >= cx; xx--)
	    for (int yy = cy - camScale*cy*cylHeight; !rightB && yy <= cy; yy++)
		if (color(gry, xx, yy) >= clrLmt)
		    rightB = xx;
	Pt.x = (leftB + rightB)/2;
	for (int yy = bottomB; !LB && !RB && yy > bottomB + camScale*cylHeight*cy/2; y--)
	{
	    if (color(gry, cx + cylWidth*cy*camScale/4, bottomB) >= clrLmt || color(gry, cx + cylWidth*cy*camScale/4 + 1, bottomB) >= clrLmt || 
		color(gry, cx + cylWidth*cy*camScale/4 - 1, bottomB) >= clrLmt)
		LB = yy;
	    if (color(gry, cx + 3*cylWidth*cy*camScale/4, bottomB) >= clrLmt || color(gry, cx + 3*cylWidth*cy*camScale/4 + 1, bottomB) >= clrLmt || 
		color(gry, cx + 3*cylWidth*cy*camScale/4 - 1, bottomB) >= clrLmt)
		RB = yy;
	}
	if (LB && RB)
	    Pt.y = (LB + RB)/2;
	else
	    Pt.y = bottomB;
	return true;
    }
    else return false;
}



#endif
