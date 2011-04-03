/**
Filename:	main.cpp

This is the main program that will be run by the robot. It calls upon all of the code in /src.
*/

#include "src/vision/vision.h"
#include "src/mci/mci.h"
#include "src/nav/navigation.h"
#include "src/sensors/sensors.h"
#include "src/vision/vision.h"
using namespace std;

int main() {
	//DECLARATIONS
	Bot me = Bot();		//this includes the sensors as well
	Map map = Map();	//this is all of the cylinders

	me.driveToMainLine();

	//RUN THE STANDARD 'SCRIPT'
	while(true) {
		me.followLineTo(map.blueCyl,  me.STD_STOP_DIST);
		me.homeInOn(map.greenCyl, me.STD_STOP_DIST);

		me.homeInOn(map.redCyl,   me.TOUCH_DIST);	
		me.chargeFor(20);			//TODO make this more sophisticated if possible

		me.homeInOn(map.greenCyl, me.STD_STOP_DIST);
		me.homeInOn(map.blueCyl,  me.STD_STOP_DIST);

		me.followLineTo(map.yellowCyl,me.TOUCH_DIST);
		me.dischargeFor(20);	   	//TODO make this more sophisticated if possible
	}

}
