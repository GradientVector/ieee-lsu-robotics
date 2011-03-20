/**
Filename:	main.cpp

This is the main program that will be run by the robot. It calls upon all of the code in /src.

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

int main() {
	//DECLARATIONS
	Bot me = new Bot();				//this includes the sensors

	CartesianPoint bluePoint   = CartesianPoint(6, 90);
	CartesianPoint greenPoint  = CartesianPoint(90, 90);
	CartesianPoint redPoint    = CartesianPoint(72, 12);
	CartesianPoint yellowPoint = CartesianPoint(6, 6);

	Cylinder blueCyl   = new Cylinder(BLUE,   bluePoint);
	Cylinder greenCyl  = new Cylinder(GREEN,  greenPoint);
	Cylinder redCyl    = new Cylinder(RED,    redPoint);
	Cylinder yellowCyl = new Cylinder(YELLOW, yellowPoint);
	//TODO: create one (BLACK) for the lines?


	//TODO:drive to the line

	//RUN THE STANDARD 'SCRIPT'
	while(true) {
		me.homeInOn(blueCyl,  me.STD_STOP_DIST);
		me.homeInOn(greenCyl, me.STD_STOP_DIST);
		me.homeInOn(redCyl,   me.TOUCH_DIST);	 
		//TODO: wait and charge
		me.homeInOn(greenCyl, me.STD_STOP_DIST);
		me.homeInOn(yellowCyl,me.STD_STOP_DIST);
		//TODO: wait and discharge
	}

}
