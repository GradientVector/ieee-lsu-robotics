
#include "Bot.h"

Bot::Bot() : STD_STOP_DIST(6), TOUCH_DIST(0), WHL_DIAM(6.6), MAX_SPEED(25), MAX_ROT_SPEED(400), IN_PER_SEC(5), DEG_PER_SEC(5)
{
    //intentionally blank
}

//Will only be used once. Gets us from the starting point (facing 'eastward') 
//to the T-junction of the black lines, facing 'northward'. After that, we can follow the right line. 
void Bot::driveToMainLine() {
   setVel(getCOMFY_SPEED());
   wait((18/getCOMFY_SPEED())*1000);		//*1000, converting s to ms
   setVel(0);
   setRotVel(getCOMFY_TURN_SPEED());
   wait((90/getCOMFY_TURN_SPEED())*1000);	//*1000, converting s to ms
   setRotVel(0);
}

/*
//checked out by Andrew Elias
//Input must either be the yellow, blue or green cylinder. We will not line-follow to the red.
//'distanceToTravel' is the 
void Bot::goToLineAndFollowItTo(Cylinder cyl, double distanceToTravel) {
    pointTo(cyl);

    //TODO: recognize line & place it in real life
    PhysicalLine physicalLine = ??; //TODO


    if(TODO: "we're not on the line" ) {
        getOn( TODO: the line);  
        pointTo(cyl);   //TODO: mabye this can be somehow include in getOn(PhysicalLine). That might be more precise.  
    } else {
        pointTo(cyl); 
    }   
	
    lineFollow(distanceToTravel);
}
*/

//uses our rough 'map' to point in the general direction of our destination.
void Bot::pointTo(Cylinder cyl) {
	setVel(0);
	//use trig to figure the angle&distance to cyl
	double deltaX = cyl.location.x - location.x;
	double deltaY = cyl.location.y - location.y;
	double direction = (DEGREES_PER_RADIAN)*atan(deltaY/deltaX);		//the direction we want to point 
	if(deltaY < 0) direction = 180 - direction;					//deals with quadrant problems

	//TODO use setRotVel(...) to do the physical motion

}

double Bot::getWHL_RADIUS() {
    return WHL_DIAM / 2;
}

double Bot::getCOMFY_SPEED() {
    return 0.5 * MAX_SPEED;
}

double Bot::getCOMFY_TURN_SPEED() {
    return 0.5 * MAX_ROT_SPEED;
}

//These two functions will rely on our charge, our charging speed, time left on the clock, etc. 
//I will work on what exact inputs they need. -Andrew Elias

//Input: 'time' is in seconds
void Bot::chargeFor(double time) {
	wait(time*1000);		//TODO can be more complex than this
}

//Input: 'time' is in seconds
void Bot::dischargeFor(double time) {
	wait (time*1000);		//TODO can be more complex than this
}

/*
These four functions return the component of the velocities 
of the individual wheels due to 'velocity' and 'rotVel': */

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
	double newLeftSettingDouble  = (velocity + getLSpeedDueToRotVel()) / IN_PER_SEC;
	double newRightSettingDouble = (velocity + getRSpeedDueToRotVel()) / IN_PER_SEC;
    int newLeftSetting = (int)(newLeftSettingDouble + 0.5);
    int newRightSetting = (int)(newRightSettingDouble + 0.5);
	if (velocity != oldVel) mci.setVelocity( newLeftSetting, newRightSetting );
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
	if(fabs(inputRotVel) > MAX_ROT_SPEED) {	
		rotVel = MAX_ROT_SPEED * inputRotVelSign;		
	} else {
		rotVel = inputRotVel;
	}

	//Convert rotational velocity (deg/sec) to linear wheel velocity (in/sec)
	//note: at this point, rotVel is in degrees per second
	double rotVelInRadPerSec = rotVel * (RADIANS_PER_DEGREE);    //rotVel in radians per second;
	double wheelVel = getWHL_RADIUS() * rotVelInRadPerSec;   //linear velocity of the right(?) wheel due to the rotational velocity; in inches/sec

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
    turn(cylPolar.getTh());
    if (cylPolar.getR() > 0) {
        moveForward(cylPolar.getR());
        while ( cylPolar.getR() > fabs(distance) ) {
            cylPolar = searchFor(cyl);
            turn(cylPolar.getTh());
            moveForward(cylPolar.getR());
        }
    }
}


/*
 * Input: Cylinder object to look for
 * Output: Returns PolarPoint object with: distance from bot itself, and angle from the bot's pointing-angle
 */
PolarPoint Bot::searchFor(Cylinder cyl){
    PixelPoint cylPoint = camera.findObject(cyl);		//TODO check: should return (0,0) if not found
    bool cylFound = (cylPoint.x != 0 && cylPoint.y != 0);
	
    double searchSpeed = 0.25 * getCOMFY_TURN_SPEED();       // Speed at which robot rotates while looking for a cylinder

    if (!cylFound){
        turnLeft(30);                  // Starts search by turning left 30 degrees
        
        int degreesTurned = 0;		//makes sure we don't turn too much
        int turningAmount = 15;		//degrees to turn, per re-check
        while( !cylFound && (degreesTurned <= 360 ) )  {  
            turnRight(turningAmount);
            cylPoint = camera.findObject(cyl);
            cylFound = (cylPoint.x != 0 && cylPoint.y != 0);
            degreesTurned += turningAmount;
        }
    }

    PolarPoint cylPolar;  //value to be returned
    if(cylFound){
        cylPolar = camera.placeObject(cylPoint);
    } else {
        cylPolar = PolarPoint(0,0);
    }

    return cylPolar;  
}


void Bot::move(bool direction, double distance, double speed){
    startMoving(direction, speed);
    wait((distance/Bot.getVel())*1000);
    stopMoving();
}

void Bot::move(bool direction, double distance){
    move(direction, distance, getCOMFY_SPEED() );
}

void Bot::startMoving(bool direction, double speed){
     if (direction){		//if LEFT
        Bot.setVel(speed);
    } else {
        Bot.setVel(-speed);
    }
}

void Bot::startMoving(bool direction){
    startMoving(direction, getCOMFY_SPEED() );
}

void Bot::moveForward(double distance, double speed){
    move(Bot.FORWARD, distance, speed);
}

void Bot::moveForward(double distance){
    moveForward( distance, getCOMFY_SPEED() );
}

void Bot::moveBackward(double distance, double speed){
    move(Bot.BACKWARD, distance, speed);
}

void Bot::moveBackward(double distance){
    moveBackward(distance, COMFY_SPEED);
}

void Bot::startMovingForward(double speed){
    startMoving(Bot.FORWARD, speed);
}

void Bot::startMovingForward(){
    startMovingForward( getCOMFY_SPEED() );
}

void Bot::startMovingBackward(double speed){
    startMoving(Bot.FORWARD, speed);
}

void Bot::startMovingBackward(){
    startMovingBackward( getCOMFY_SPEED() );
}

void Bot::stopMoving(){
    setRotVel(0);
}

//Input is in degrees, with positive being leftward. The bot refuses to turn more than 180 degrees.
void Bot::turn(double inputAngle){
    //any turn >180 should be rethought; going the other way may be faster
    int inputAngleSign; // 1 or -1 depending on positivity of inputAngle
    if (fabs(inputAngle) > 180) {
        inputAngleSign = inputAngle / fabs(inputAngle);    
        while(fabs(inputAngle) > 180) {
            inputAngle -= inputAngleSign * 180;
        }    
    } 

    if(inputAngle > 0) {
        turn(Bot.LEFT, fabs(inputAngle));
    } else if (inputAngle < 0) {
        turn( Bot.RIGHT, fabs(inputAngle) );
    } //and if inputAngle == 0, do nothing
}

void Bot::turn(bool direction, double inputAngle){
    startTurning(direction, COMFY_TURN_SPEED);
    wait( (inputAngle/Bot.getRotVel())*1000 );
    stopTurning();
}

void Bot::turnLeft(double inputAngle){
    turn(Bot.LEFT, inputAngle, COMFY_TURN_SPEED);
}

void Bot::turnRight(double inputAngle){
    turn(Bot.RIGHT, inputAngle, COMFY_TURN_SPEED);
}

void Bot::startTurning(bool direction, double speed){
     if (direction){
        Bot.setRotVel(speed);
    } else {
        Bot.setRotVel(-speed);
    }
}

void Bot::startTurning(bool direction){
    startTurning(direction, getCOMFY_TURN_SPEED() );
}

void Bot::stopTurning(){
    setRotVel(0);
}
