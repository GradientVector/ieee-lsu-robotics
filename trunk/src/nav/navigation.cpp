/**
Filename:	navigation.cpp

This, along with navigation.h, contain all functionality necessary for moving around and rough cartography.

LOG:
	2011 Feb 24 - blank document created by Andrew Elias
	2011 Mar 18 - driveToMainLine(), chargeFor(), dischargeFor() added by Andrew Elias


 */

#ifndef _NAVIGATION_CPP_
#define _NAVIGATION_CPP_

#include <math.h>
#include "mci.h"
#include "navigation.h"

//Will only be used once. Gets us from the starting point (facing 'eastward') 
//to the T-junction of the black lines, facing 'northward'. Then we can follow the right line. 
void Bot::driveToMainLine() {
	//TODO
   
   setVel(COMFY_SPEED);
   wait((18/COMFY_SPEED)*1000);
   setvel(0);
   setRotVel(COMFY_TURN_SPEED);
   wait((90/COMFY_TURN_SPEED)*1000);
   setRotVel(0);
}

//Input must either be the yellow or blue cylinder. We will not line-follow to the others.
void Bot::followLineTo(Cylinder cyl, double distance) {
	//TODO
}

//uses our rough 'map' to point in the general direction of our destination.
void Bot::pointTo(Cylinder cyl) {
	double deltaX = cyl.location.x - me.location.x;
	double deltaY = cyl.location.y - me.location.y;
	double direction = (180/3.1415926)*atan(deltaY/deltaX);		//the direction we want to point TODO note may have to do math.atan? also: converted from rad to degrees
	if(deltaY < 0) direction = 180 - direction;
	//TODO use setRotVel(...) to do the physical motion
}

void Bot::homeInOn(Cylinder cyl, double distance) {
	pointTo(cyl);
	//TODO
		//note: when going to either blue from yellow or to yellow from blue, follow the line first.

	//note: first point towards it, then look for it, then move towards it.
}

void Bot::chargeFor(/*TODO*/) {
	//TODO
}

void Bot::dischargeFor(/*TODO*/) {
	//TODO
}

PolarPoint::PolarPoint(double in_r, Angle in_th){
    r = in_r;
    th = in_th;
}
PolarPoint::PolarPoint(double in_r, double in_th){
    r = in_r;
    th.setAngle(in_th);
}

PolarPoint::PolarPoint(){
    r = 0.0;
    th.setAngle(0.0);

//These two functions will rely on our charge, our charging speed, time left on the clock, etc. 
//I will work on what exact inputs they need. -Andrew Elias


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

double Bot::getVel() {
	return velocity;
}

//units: inches/sec
void Bot::setVel(double newVelocity){
	double SCALING_FACTOR = 2; //multiply by this to convert from in/sec to MCI-units TODO this is wrong; email Del
	double dV =   ; //change in velocity due to this function
	double
	
	//TODO
	mci.setVelocity(/*blank until we know units*/);  //TODO
	velocity = newVelocity;
}

double Bot::getRotVel() {
	return rotVel;
}

//units: degrees/sec
void Bot::setRotVel(double newRotVel){
	double radius = WHL_DIAM/2;
	double newRotVelInRadians = (180/3.1415926)*newRotVel;
	velToSetEach = radius*newRotVelInRadians;		//the vel for each wheel, in in/sec
	const double SCALING_FACTOR = 2; 		//TODO this is wrong, email Del
	double toSet = SCALING_FACTOR*velToSetEach;		
	//TODO set the rot vel without unsetting the vel

	mci.setVelocity(/*blank until we know units*/);  //TODO
	rotVel = newRotVel;
}

CartesianPoint::CartesianPoint(double x, double y) {
	x = xPassed;
	y = yPassed;
}

#endif
