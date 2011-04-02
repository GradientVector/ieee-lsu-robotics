
#include "Bot.h"
#include <math.h>

//DONE
//Will only be used once. Gets us from the starting point (facing 'eastward') 
//to the T-junction of the black lines, facing 'northward'. After that, we can follow the right line. 
void Bot::driveToMainLine() {
   setVel(COMFY_SPEED);
   wait((18/COMFY_SPEED)*1000);		//*1000, converting s to ms
   setVel(0);
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

//checked out by Andrew Elias
//units: inches/sec
void Bot::setVel(double newVelocity){
	double oldVel = velocity;
	if(fabs(newVelocity) > MAX_SPEED) {	
		velocity = MAX_SPEED;		
	} else {
		velocity = newVelocity;		
	}

	double dV = velocity - oldVelocity;   //change in velocity due to this function

	//convert them from in/sec to a scale of -1 to 1, to be usable by the MCI code
	dV     = dV     / SCALING_FACTOR; 		      
	oldVel = oldVel / SCALING_FACTOR;

	mci.setModeStatus(mci.MIXED_MODE);	//MIXED_MODE indicates vel/rotVel instead of L/R
	mci.setVelocity(oldVel + dV, rotVel/SCALING_FACTOR);  
	//TODO convert MAX_SPEED to SCALING_FACTOR?
}

//DONE
double Bot::getRotVel() {
	return rotVel;
}

//checked out by ANDREW ELIAS
//units: degrees/sec
void Bot::setRotVel(double newRotVel){
	double oldRotVel = rotVel;
	if(fabs(newRotVel) > MAX_ROT_SPEED) {	
		rotVel = MAX_ROT_SPEED;		
	} else {
		rotVel = newRotVel;		
	}

	double dRV = rotVel - oldRotVel;   //change in rotational velocity due to this function

	//convert them from in/sec to a scale of -1 to 1, to be usable by the MCI code
	dRV       = dRV       / SCALING_FACTOR; 		      
	oldRotVel = oldRotVel / SCALING_FACTOR;

	mci.setModeStatus(mci.MIXED_MODE);	//MIXED_MODE indicates vel/rotVel instead of L/R
	mci.setVelocity(velocity/SCALING_FACTOR, oldRotVel + dRV); 

	//TODO: should there be a ROT_SCALING_FACTOR referring to MCI's interpretation of "1" when passed as a rotational velocity?

	//TODO: this code may still be needed; keep it here for now
	/*
	double radius = WHL_DIAM/2;
	double newRotVelInRadians = (180/3.1415926)*newRotVel;
	velToSetEach = radius*newRotVelInRadians;		//the vel for each wheel, in in/sec
	double toSet = SCALING_FACTOR*velToSetEach;		
	//TODO set the rot vel without unsetting the vel

	mci.setVelocity(  blank until we know units   );  //TODO
	rotVel = newRotVel;
	*/
}
dr


//homes in on an object until it gets to a certain distance away from the object.
void Bot::homeInOn(Cylinder cyl, double distance) {
    PolarPoint cylPolar;
    double close_enough = 0;   // Tolerance for distance

    pointTo(cyl);

    cylPolar = searchFor(cyl);
    turnTo(cylPolar.th.getAngle());
    if (cylPolar.r > 0){
        moveForwardTo(cylPolar.r);
        while ((cylPolar.r - fabs(distance))> close_enough){
            cylPolar = searchFor(cyl);
            turnTo(cylPolar.th.getAngle());
            moveForwardTo(cylPolar.r);
        }
    }
}


/*
 * searchFor function
 * Input: Cylinder object to look for
 * Output: Returns PolarPoint object with distance from

 */
PixelPoint Bot::searchFor(Cylinder cyl){
    PixelPoint cylPoint;                               // Cylinder base point (pixel) on image, (0,0) if not found
    PolarPoint cylPolar;                               // Returned object, polar description of position of cylinder relative to robot
    bool cylFound;                                     // Boolean set for loop purposes- tracks if cylinder has been found
    int searchTimeLeft = 30000;                        // (30s) Time in ms that robot spends rotating while searching for a cylinder
    double searchSpeed = .25 * COMFY_TURN_SPEED;       // Speed at which robot rotates while looking for a cylinder

    cylPoint = findObject(cyl);
    cylFound = (cylPoint.x != 0 && cylPoint.y != 0);

    if (!cylFound){
        turnLeft(55);                  // Starts search by turning left 55 degrees
        startTurnRight(searchSpeed);   //change to be optimal based on current position on map?
        while(!cylFound && searchTimeLeft){
            cylPoint = findObject(cyl);
            cylFound = (cylPoint.x != 0 && cylPoint.y != 0);
            wait(angle/searchSpeed*1000);
            searchTimeLeft -= 1000;
        }
        stopTurn();
    }
    if(cylFound){
        placeObject(cylPoint);
    } else {
        cylPolar.setPolarPoint(0,0);
    }
    return cylPolar;
}


/* Begin move forward/backward functions */
void Bot::moveTo(bool direction, double distance, double speed = COMFY_SPEED){
    startMove(direction, speed);
    wait((distance/Bot.getVel())*1000);
    stopMove();
}

void Bot::startMove(bool direction, double speed = COMFY_SPEED){
     if (direction){
        Bot.setVel(speed);
    } else {
        Bot.setVel(-speed);
    }
}

void Bot::moveForwardTo(double distance, double speed = COMFY_SPEED){
    moveTo(Bot.FORWARD, distance, speed);
}

void Bot::moveBackwardTo(double distance, double speed = COMFY_SPEED){
    moveTo(Bot.BACKWARD, distance, speed);
}

void Bot::startMoveForward(double speed = COMFY_SPEED){
    startMove(Bot.FORWARD, speed);
}

void Bot::startMoveBackward(double speed = COMFY_SPEED){
    startMove(Bot.FORWARD, speed);
}

void Bot::stopMove(){
    setRotVel(0);
}
/* End move (forward/backward) functions */


/* Begin turn (left/right) functions*/
void Bot::turnTo(double angle, double speed = COMFY_TURN_SPEED){
    angle -= 180;
    if(angle < 0){
        turn(Bot.LEFT, fabs(angle), speed);
    } else if (angle > 0) {
        turn(Bot.RIGHT, fabs(angle), speed);
    }
}

void Bot::turnTo(Angle angle, double speed = COMFY_TURN_SPEED){
    turnTo(angle.getAngle(),speed);
}

void Bot::turn(bool direction, double angle, double speed = COMFY_TURN_SPEED){
    startTurn(direction, speed);
    wait((angle/Bot.getRotVel())*1000);
    stopTurn();
}

void Bot::turn(bool direction, Angle angle, double speed = COMFY_TURN_SPEED){
    turn(direction, angle.getAngle(),speed);
}

void Bot::startTurn(bool direction, double speed = COMFY_TURN_SPEED){
     if (direction){
        Bot.setRotVel(speed);
    } else {
        Bot.setRotVel(-speed);
    }
}

void Bot::turnLeft(double angle, double speed = COMFY_TURN_SPEED){
    turn(Bot.LEFT, angle, speed);
}

void Bot::turnRight(double angle, double speed = COMFY_TURN_SPEED){
    turn(Bot.RIGHT, angle, speed);
}

void Bot::startTurnLeft(double speed = COMFY_TURN_SPEED){
    startTurn(Bot.LEFT, speed);
}

void Bot::startTurnRight(double speed = COMFY_TURN_SPEED){
    startTurn(Bot.RIGHT, speed);
}

void Bot::stopTurn(){
    setRotVel(0);
}
/* End turn (left/right) functions*/
