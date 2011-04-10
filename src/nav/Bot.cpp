
#include "Bot.h"
#include <math.h>

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

//checked out by Andrew Elias
//Input must either be the yellow, blue or green cylinder. We will not line-follow to the red.
//'distanceToTravel' is the 
void Bot::goToLineAndFollowItTo(Cylinder cyl, double distanceToTravel) {
    pointTo(cyl);

    //TODO: recognize line & place it in real life
    PhysicalLine physicalLine = ??; //TODO


    if(/*TODO: "we're not on the line" */) {
        getOn(/* TODO: the line*/);  
        pointTo(cyl);   //TODO: mabye this can be somehow include in getOn(PhysicalLine). That might be more precise.  
    } else {
        pointTo(cyl); 
    }   
	
    lineFollow(distanceToTravel);
}

//uses our rough 'map' to point in the general direction of our destination.
void Bot::pointTo(Cylinder cyl) {
	setVel(0);
	//use trig to figure the angle&distance to cyl
	double deltaX = cyl.location.x - me.location.x;
	double deltaY = cyl.location.y - me.location.y;
	double direction = (DEGREES_PER_RADIAN)*atan(deltaY/deltaX);		//the direction we want to point 
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

/*
These four functions return the component of the velocities 
of the individual wheelsdue to 'velocity' and 'rotVel': */

//returns (signed) speed of left wheel (in/sec) due to robot's velocity
double Bot::getRSpeedDueToVel() {
	return velocity;
}

//returns (signed) speed of left wheel (in/sec) due to robot's velocity
double Bot::getLSpeedDueToVel() {
	return velocity;
}

//returns (signed) speed of right wheel due to robot's rotational velocity
double Bot::getRSpeedDueToRotVel() {
	double rotVelInRadPerSec = rotVel * RADIANS_PER_DEGREE;   //RADIANS_PER_DEGREE defined in util.h
	return rotVelInRadPerSec;                             //no negation
}

//returns (signed) speed of left wheel due to robot's rotational velocity
double Bot::getLSpeedDueToRotVel() {
	double rotVelInRadPerSec = rotVel * RADIANS_PER_DEGREE;   //RADIANS_PER_DEGREE defined in util.h
	return rotVelInRadPerSec * -1;                        //with negation because it's the left wheel
}

double Bot::getVel() {
	return velocity;
}

//input units: inches/sec
void Bot::setVel(double inputVelocity){
	double oldVel = velocity;

	int inputVelSign;    //sign(+/-) of the velocity passed
	if (inputVelocity > 0) inputVelSign =  1;
		else            inputVelSign = -1;

	//don't let the user set it higher than max speed
	if(fabs(inputVelocity) > MAX_SPEED) {	
		velocity = MAX_SPEED * inputVelSign;		
	} else {
		velocity = inputVelocity;		
	}

	//physically set it
	double newLeftSetting  = (velocity + getLSpeedDueToRotVel()) / IN_PER_SEC;
	double newRightSetting = (velocity + getRSpeedDueToRotVel()) / IN_PER_SEC;
	if (velocity != oldVel) mci.setVelocity( newLeftSetting, newRightSetting);
}

double Bot::getRotVel() {
	return rotVel;
}

//units: degrees/sec
void Bot::setRotVel(double inputRotVel) {
	double oldRotVel = rotVel;

	int inputRotVelSign;    //sign(+/-) of the rotational velocity passed
	if (inputRotVel > 0) inputRotVelSign =  1;
		else            inputRotVelSign = -1;

	//don't let the user set it higher than max rot speed
	if(fabs(inputVelocity) > MAX_ROT_SPEED) {	
		rotVel = MAX_ROT_SPEED * inputRotVelSign;		
	} else {
		rotVel = inputRotVel;
	}

	//Convert rotational velocity (deg/sec) to linear wheel velocity (in/sec)
	//note: at this point, rotVel is in degrees per second
	double rotVelInRadPerSec = rotVel * (RADIANS_PER_DEGREE);    //rotVel in radians per second;
	double wheelVel = WHL_RADIUS * rotVelInRadPerSec;   //linear velocity of the right(?) wheel due to the rotational velocity; in inches/sec

	//physically set it
	double newLeftSetting  = (getLSpeedDueToRotVel() - wheelVel) / IN_PER_SEC;
	double newRightSetting = (getRSpeedDueToRotVel() + wheelVel) / IN_PER_SEC;
	if (rotVel != oldRotVel) mci.setVelocity( newLeftSetting, newRightSetting);

	//TODO check all of this

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
    startTurning(direction, speed);
    wait((angle/Bot.getRotVel())*1000);
    stopTurning();
}

void Bot::turn(bool direction, Angle angle, double speed = COMFY_TURN_SPEED){
    turn(direction, angle.getAngle(),speed);
}

void Bot::startTurning(bool direction, double speed = COMFY_TURN_SPEED){
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

void Bot::startTurningLeft(double speed = COMFY_TURN_SPEED){
    startTurning(Bot.LEFT, speed);
}

void Bot::startTurningRight(double speed = COMFY_TURN_SPEED){
    startTurning(Bot.RIGHT, speed);
}

void Bot::stopTurning(){
    setRotVel(0);
}
/* End turn (left/right) functions*/
