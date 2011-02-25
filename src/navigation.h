/**
Filename:	navigation.h
	
This, along with navigation.cpp, hold instructions for movement and rough geographical positioning.

Log:	2011 Feb 25 - document created by Andrew Elias

TODO list:
	


*/

#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_



//holds a location on a map; units are inches.
//by convention the origin is the lower lefthand side of the map.
class CartesianPoint {
	public:
		double x;	//units: inches
				//x==0 indicates the bottom of the map
		double y;
				//y==0 indicates the left side of the map
};

//will be used to hold a relative position, in polar coordinates.
//This will help us know what angle we need to turn to face an object.
class PolarPoint {
	public:
		double r;	//radial  coordinate. units: inches
				//r==0 indicates our (the robot's) position
		double th;	//angular coordinate. units: degrees
				//th==0 indicates directly ahead of us
				//note: 'th' indicates 'theta'
};

void homeInOn(Cylinder, double distance) {
	//TODO
}

#endif
