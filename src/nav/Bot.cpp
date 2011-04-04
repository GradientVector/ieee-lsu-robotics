
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
	if(deltaY < 0) direction = 180 - direction;					//deals with quadrant problems
	//TODO use setRotVel(...) to do the physical motion
}

//These two functions will rely on our charge, our charging speed, time left on the clock, etc. 
//I will work on what exact inputs they need. -Andrew Elias
//Input: 'time' is in seconds
void Bot::chargeFor(double time) {
	wait(time*1000);		//TODO can be more complex than this
}

void Bot::dischargeFor(double time) {
	wait (time*1000);		//TODO can be more complex than this
}

//DONE
double Bot::getVel() {
	return velocity;
}

//checked out by Andrew Elias
//units: inches/sec
void Bot::setVel(double newVelocity){
	double oldVel = velocity;

	int newVelSign;
	if (newVelocity > 0) newVelSign =  1;
		else            newVelSign = -1;

	if(fabs(newVelocity) > MAX_SPEED) {	
		velocity = MAX_SPEED * newVelSign;		
	} else {
		velocity = newVelocity;		
	}

	double dV = velocity - oldVelocity;   //change in velocity due to this function

	//convert them from in/sec to a scale of -1 to 1, to be usable by the MCI code
	dV     = dV     / SCALING_FACTOR; 		      
	oldVel = oldVel / SCALING_FACTOR;

	mci.setModeStatus(mci.MIXED_MODE);	//MIXED_MODE indicates vel/rotVel instead of L/R
	mci.setVelocity( (oldVel + dV)/SCALING_FACTOR, rotVel/ROT_SCALING_FACTOR );  //TODO correct rotVel value passed?
}

//DONE
double Bot::getRotVel() {
	return rotVel;
}

//checked out by ANDREW ELIAS
//units: degrees/sec
void Bot::setRotVel(double newRotVel){
	double oldRotVel = rotVel;

	int newRotVelSign;			//positive for newRotVel>0, negative otherwise
	if (newRotVel > 0) newRotVelSign =  1;
		else          newRotVelSign = -1;

	if(fabs(newRotVel) > MAX_ROT_SPEED) {	
		rotVel = MAX_ROT_SPEED * newRotVelSign;		
	} else {
		rotVel = newRotVel;		
	}

	double dRV = rotVel - oldRotVel;   //change in rotational velocity due to this function

	mci.setModeStatus(mci.MIXED_MODE);	//MIXED_MODE indicates vel/rotVel instead of L/R
	mci.setVelocity( velocity/SCALING_FACTOR, (oldRotVel + dRV)/ROT_SCALING_FACTOR ); 


	//TODO: this code may still be needed; keep it here for now  -AndrewE
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


//homes in on an object until it gets to a certain distance away from the object.
void Bot::homeInOn(Cylinder cyl, double distance) {
    pointTo(cyl);

    PolarPoint cylPolar = searchFor(cyl);
    turnTo(cylPolar.th.getAngle());
    if (cylPolar.r > 0){
        moveForwardTo(cylPolar.r);
        while ( cylPolar.r > fabs(distance) ){
            cylPolar = searchFor(cyl);
            turnTo(cylPolar.th.getAngle());
            moveForwardTo(cylPolar.r);
        }
    }
}


/*
 * Input: Cylinder object to look for
 * Output: Returns PolarPoint object with: distance from bot itself, and angle from the bot's pointing-angle
 */
PolarPoint Bot::searchFor(Cylinder cyl){
    PixelPoint cylPoint = findObject(cyl);		//TODO check: should return (0,0) if not found
    bool cylFound = (cylPoint.x != 0 && cylPoint.y != 0);
	
    double searchSpeed = 0.25 * COMFY_TURN_SPEED;       // Speed at which robot rotates while looking for a cylinder

    if (!cylFound){
        turnLeft(30);                  // Starts search by turning left 30 degrees
        
        int degreesTurned = 0;		//makes sure we don't turn too much
        int turningAmount = 15;		//degrees to turn, per re-check
        while( !cylFound && (degreesTurned <= 360 ) )  {  
            turnRight(turningAmount);
            cylPoint = findObject(cyl);
            cylFound = (cylPoint.x != 0 && cylPoint.y != 0);
            degreesTurned += turningAmount;
        }
    }

    PolarPoint cylPolar;  //value to be returned
    if(cylFound){
        cylPolar = placeObject(cylPoint);
    } else {
        cylPolar = PolarPoint(0,0);
    }

    return cylPolar;  
}


/* Begin move forward/backward functions */
void Bot::moveTo(bool direction, double distance, double speed = COMFY_SPEED){
    startMoving(direction, speed);
    wait((distance/Bot.getVel())*1000);
    stopMoving();
}

void Bot::startMoving(bool direction, double speed = COMFY_SPEED){
     if (direction){		//if LEFT
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

void Bot::startMovingForward(double speed = COMFY_SPEED){
    startMoving(Bot.FORWARD, speed);
}

void Bot::startMovingBackward(double speed = COMFY_SPEED){
    startMoving(Bot.FORWARD, speed);
}

void Bot::stopMoving(){
    setRotVel(0);
}
/* End move (forward/backward) functions */


/* Begin turn (left/right) functions*/
void Bot::turnTo(double angle, double speed = COMFY_TURN_SPEED){
    angle -= 180;		//TODO 'angle' is already a Bot member variable. also, does this represent a destation angle, or an angle of turning?
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
