/**
Filename:	main.cpp

This is the main program that will be run by the robot. It calls upon all of the code in /src.
*/

#include "src/mci/mci.h"
#include "src/nav/navigation.h"
#include "src/nav/Bot.h"
#include "src/nav/Map.h"
#include "src/vision/vision.h"
#include "src/util/util.h"
using namespace std;

//there is no function called followLineTo in bot.h

int main() {
	//DECLARATIONS
	Bot me = Bot();		//this includes the sensors as well
	Map map = Map();	//this is all of the cylinders

	//wait a little while to allow the button-presser to back off from the bot
	wait(1500);		//1.5 seconds
	
	me.driveToMainLine();

	//RUN THE STANDARD 'SCRIPT'
	while(true) {
		me.goToLineAndfollowItTo(map.blueCyl,  me.STD_STOP_DIST);
		me.homeInOn(map.greenCyl, me.STD_STOP_DIST);

		me.homeInOn(map.redCyl,   me.TOUCH_DIST);	
		me.chargeFor(20);			//TODO make this more sophisticated if possible

		me.homeInOn(map.greenCyl, me.STD_STOP_DIST);
		me.homeInOn(map.blueCyl,  me.STD_STOP_DIST);

		me.goToLineAndfollowItTo(map.yellowCyl,me.TOUCH_DIST);
		me.dischargeFor(20);	   	//TODO make this more sophisticated if possible
	}

}
