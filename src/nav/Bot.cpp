
#include "Bot.h"
#include <math.h>

//Will only be used once. Gets us from the starting point (facing 'eastward') 
//to the T-junction of the black lines, facing 'northward'. Then we can follow the right line. 
void Bot::driveToMainLine() {
	//TODO
   
   setVel(COMFY_SPEED);
   wait((18/COMFY_SPEED)*1000);		//*1000, converting s to ms
   setvel(0);
   setRotVel(COMFY_TURN_SPEED);
   wait((90/COMFY_TURN_SPEED)*1000);	//*1000, converting s to ms
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
	double direction = (180/3.1415926)*atan(deltaY/deltaX);		//the direction we want to point 
	if(deltaY < 0) direction = 180 - direction;			//deals with quadrant problems
	//TODO use setRotVel(...) to do the physical motion
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

//DONE
double Bot::getVel() {
	return velocity;
}

//checked out by ANDREW ELIAS
//units: inches/sec
void Bot::setVel(double newVelocity){
	double SCALING_FACTOR = 2; //number of inches/sec represented by "1" being passed to 
	//multiply by this to convert from in/sec to MCI-units 
	//TODO this is wrong; must determine it empirically. also, move it to .h file

	double oldVel = velocity;
	if(fabs(newVelocity) > MAX_SPEED) {	
		velocity = MAX_SPEED;		
	} else {
		velocity = newVelocity;		
	}

	double dV = velocity - oldVelocity;   //change in velocity due to this function

	//convert them from in/sec to a scale of -1 to 1
	dV     = dV     / MAX_SPEED; 		      
	oldVel = oldVel / MAX_SPEED

	mci.setModeStatus(mci.MIXED_MODE);	//MIXED_MODE indicates vel/rotVel instead of L/R
	mci.setVelocity(oldVel + dV, rotVel/MAX_SPEED);  
	//TODO check all of this!
}

//DONE
double Bot::getRotVel() {
	return rotVel;
}

//checked out by ANDREW ELIAS
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
