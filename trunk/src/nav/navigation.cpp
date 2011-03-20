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

void Bot::homeInOn(Cylinder, double distance) {
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


#endif
