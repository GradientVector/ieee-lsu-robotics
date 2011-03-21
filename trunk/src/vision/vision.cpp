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

Cylinder::Cylinder(int colorPassed, CartesianPoint locationPassed) {
	color = colorPassed;
	location = locationPassed;
}

PixelPoint findObject(Cylinder) {
	//TODO John West: paste your code here
}

PolarPosition placeObject(PixelPoint) {
	//TODO
}




#endif
