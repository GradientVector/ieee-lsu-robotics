/**
Filename:	main.cpp

This is the main program that will be run by the robot.

LOG:
	2011 Feb 24 - created by Andrew Elias
	2011 Mar 5  - filled in a bit; Andrew Elias

*/

#include "src/vision/vision.h"
#include "src/mci/mci.h"
#include "src/nav/navigation.h"
#include "src/sensors/sensors.h"
#include "src/vision/vision.h"
using namespace std;

const double STD_STOP_DIST = 6; 	//when navigating by homeInOn(-,-),  this is the standard stopping distance (inches) when we don't want to touch the object 

const double TOUCH_DIST = 0;		//distance from our camera to the object when we are touching it

int main() {
	//create objects to be used
	Bot me = new Bot();
	Cylinder blueCyl   = new Cylinder(BLUE);
	Cylinder greenCyl  = new Cylinder(GREEN);
	Cylinder redCyl    = new Cylinder(RED);
	Cylinder yellowCyl = new Cylinder(YELLOW);
	//TODO: create one (BLACK) for the lines?


	//TODO:drive to the line

	while(true) {
		me.homeInOn(blueCyl,  STD_STOP_DIST);
		me.homeInOn(greenCyl, STD_STOP_DIST);
		me.homeInOn(redCyl,   TOUCH_DIST);	 
		//TODO: wait and charge
		me.homeInOn(greenCyl, STD_STOP_DIST);
		me.homeInOn(yellowCyl,STD_STOP_DIST);
		//TODO: wait and discharge
	}

}
