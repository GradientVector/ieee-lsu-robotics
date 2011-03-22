/**
Filename:	navigation.h
	
This, along with navigation.cpp, hold instructions for movement and rough geographical positioning.

Log:	2011 Feb 25 - document created by Andrew Elias
	2011 Mar 18 - driveToMainLine() added by Andrew Elias

*/

#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_

#include "../sensors/sensors.h"
#include "../vision/vision.h"


//will only be instantiated once. represents the robot itself.
//Holds location and angle information.
class Bot {
	private:
	double velocity, rotVel;
	
	public:
	const double STD_STOP_DIST = 6; 	//when navigating by homeInOn(-,-),  this is the standard stopping distance(inches) when we don't want to touch the object 
	const double TOUCH_DIST = 0;		//distance(inches) from our camera to the object when we are touching it
	const double WHL_DIAM;			//separation b/t the wheels
	//good, standard speeds that aren't too fast/slow
	const double COMFY_SPEED = 6;		
	const double COMFY_TURN_SPEED = 360;
	
	SensorSet sensors;
	CartesianPoint location;
	Angle angle;
	MCI mci;

	void driveToMainLine();
	void followLineTo(Cylinder cyl, double distance);
	void pointTo(Cylinder cyl);
	void homeInOn(Cylinder, double distance);
	void chargeFor(/*TODO*/);
	void dischargeFor(/*TODO*/);
	void getVel();
	void setVel(double vel);
	void getRotVel();
	void setRotVel(double rotVel);
};


//a list of cylinders (and their colors/locations)
class Map {
	public:
	Cylinder yellowCyl;
	Cylinder blueCyl;
	Cylinder greenCyl;
	Cylinder redCyl;
	Map();
}


//holds a location on a map; units are inches.
//by convention the origin is the lower lefthand side of the map.
class CartesianPoint {
	public:
	double x;	//units: inches
				//x==0 indicates the bottom of the map
	double y;
				//y==0 indicates the left side of the map
	CartesianPoint(double xPassed, double yPassed);
};


//will be used to hold a relative position, in polar coordinates.
//This will help us know what angle we need to turn to face an object.
class PolarPoint {
	public:
	double r;	//radial  coordinate. units: inches
			//r==0 indicates our (the robot's) position
	Angle th;	//angular coordinate. units: degrees
			//th==0 indicates directly ahead of us
			//note: 'th' indicates 'theta'
        PolarPoint(double in_r, Angle in_th);
        PolarPoint(double in_r, double in_th);
        PolarPoint();
};



#endif
