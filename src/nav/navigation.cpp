/**
Filename:	navigation.cpp

This, along with navigation.h, contain all functionality necessary for moving around and rough cartography.

LOG:
	2011 Feb 24 - blank document created by Andrew Elias
	2011 Mar 18 - driveToMainLine(), chargeFor(), dischargeFor() added by Andrew Elias


 */

#ifndef _NAVIGATION_CPP_
#define _NAVIGATION_CPP_

#include "navigation.h"

//Will only be used once. Gets us from the starting point (facing 'eastward') 
//to the T-junction of the black lines, facing 'northward'. Then we can follow the right line. 
void Bot::driveToMainLine() {
	//TODO
}

//Input must either be the yellow or blue cylinder. We will not line-follow to the others.
void Bot::followLineTo(Cylinder cyl) {
	//TODO
}

//uses our rough 'map' to point in the general direction of our destination.
void Bot::pointTo(Cylinder cyl) {
	//TODO
}

void Bot::homeInOn(Cylinder cyl, double distance) {
	pointTo(cyl);
	//TODO
		//note: when going to either blue from yellow or to yellow from blue, follow the line first.

	//note: first point towards it, then look for it, then move towards it.
}

//These two functions will rely on our charge, our charging speed, time left on the clock, etc. 
//I will work on what exact inputs they need. -Andrew Elias
void Bot::chargeFor(/*TODO*/) {
	//TODO
}

void Bot::dischargeFor(/*TODO*/) {
	//TODO
}

Map::Map() {
	CartesianPoint bluePoint   = CartesianPoint(6, 90);
	CartesianPoint greenPoint  = CartesianPoint(90, 90);
	CartesianPoint redPoint    = CartesianPoint(72, 12);
	CartesianPoint yellowPoint = CartesianPoint(6, 6);

	blueCyl   = Cylinder(Cylinder.BLUE,   bluePoint);
	greenCyl  = Cylinder(Cylinder.GREEN,  greenPoint);
	redCyl    = Cylinder(Cylinder.RED,    redPoint);
	yellowCyl = Cylinder(Cylinder.YELLOW, yellowPoint);
}

void setVel(double vel){
	//TODO
}

void setRotVel(double rotVel){
	//TODO
}

CartesianPoint::CartesianPoint(double x, double y) {
	x = xPassed;
	y = yPassed;
}

#endif
