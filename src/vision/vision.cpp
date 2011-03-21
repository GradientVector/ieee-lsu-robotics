/**
Filename:	vision.cpp

This, along with vision.h, contain all functionality necessary for using the camera.

LOG:
	2011 Feb 24 - blank document created by Andrew Elias

TODO list:
	

 */

#ifndef _VISION_CPP_
#define _VISION_CPP_

#include "vision.h"
using namespace std;

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

Cylinder::Cylinder(int colorPassed, CartesianPoint locationPassed) {
	color = colorPassed;
	location = locationPassed;
}



PixelPoint::PixelPoint(int ix, int iy)
{
  x = ix;
  y = iy;
  return 0;
}


int color(Mat, int, int) //this returns a color at a point

PixelPoint findObject(cyl)

{
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

PolarPosition placeObject(PixelPoint) {
	//TODO
}

Mat GrayImage::getGI(int color)
{
  switch (color)
    case 1: return getRedPixels();
    case 2: return getGreenPixels();
    case 3: return getBluePixels();
    case 4: return getYellowPixels();
    case 5: return getLines();
}

Mat GrayImage::getRedPixels();
{
  split(img, planes);
  Mat adj(img.rows, img.cols, CV_8UC1);
  subtract(planes[2], planes[1], adj);
  subtract(adj, planes[0], adj);
  return adj;
}

Mat GrayImage::getGreenPixels();
{
  split(img, planes);
  Mat adj(img.rows, img.cols, CV_8UC1);
  subtract(planes[1], planes[2], adj);
  subtract(adj, planes[0], adj);
  return adj;
}

Mat GrayImage::getBluePixels();
{
  split(img, planes);
  Mat adj(img.rows, img.cols, CV_8UC1);
  subtract(planes[0], planes[1], adj);
  subtract(adj, planes[2], adj);
  return adj;
}

Mat GrayImage::getYellowPixels();
{
  split(img, planes);
  Mat adj(img.rows, img.cols, CV_8UC1);
  subtract(planes[1], planes[2], adj);
  add(adj, planes[0], adj);
  subtract(adj, planes[2], adj);
  return adj;
}

Mat GrayImage::getLines();
{
  Mat adj(img.rows, img.cols, CV_8UC1);
  Mat gray;
  cvtColor(img, gray, CV_BGR2GRAY);
  subtract(adj, gray, adj);
  //line detection code here, otherwise just returns inverted grayscale
  return adj;
}

#endif
