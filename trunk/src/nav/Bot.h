/*  Will only be instantiated once. represents the robot itself.
    Holds location and angle information.
*/

#ifndef BOT_H
#define BOT_H

#include <math.h>
#include "../vision/vision.h"
//#include "../sensors/sensors.h"   //TODO: remove this if we don't have a charge sensor
#include "../util/util.h"
#include "../util/Angle.h"
#include "../util/PolarPoint.h"
#include "../util/Cylinder.h"
//p#include "../util/PhysicalLine.h"
#include "../vision/Camera.h"
#include "../mci/mci.h"


class Bot {
    private:
    double velocity, rotVel;      //rotVel>0 means the bot is twisting left

    //accessors for each wheel speed due to each type of motion; returns value from -9999 to 9999 (mci scale)
    double getRSpeedDueToVel();
    double getLSpeedDueToVel();
    double getRSpeedDueToRotVel();
    double getLSpeedDueToRotVel();
	
	
    public:
    const double STD_STOP_DIST;     //when navigating by homeInOn(-,-),  this is the standard stopping distance(inches) when we don't want to touch the object 
    const double TOUCH_DIST;        //distance(inches) from our camera to the object when we are touching it

    const double WHL_DIAM;              //separation b/t the wheels
    double getWHL_RADIUS();

    //high speeds at which things start going wrong(i.e. slippage, popping wheelies, etc). Subj to change
    const double MAX_SPEED;    //inches/second
    const double MAX_ROT_SPEED;	//degrees/second

    //good, standard speeds that aren't too fast/slow.
    double getCOMFY_SPEED();
    double getCOMFY_TURN_SPEED();

    const double IN_PER_SEC;        //the speed, in in/sec, represented by passing "1,1" to the MCI's setVelocity() function; a simple unit conversion factor. TODO: value should be changed later
    const double DEG_PER_SEC;       //the rotational speed, in deg/sec, represented by passing "-1,1" (TODO) to the MCI's setVelocity() function; a simple unit conversion factor. TODO: value should be changed later

    //NOTE: directional booleans have been moved to util.h

    CartesianPoint location;
    Angle angle;
    MCI mci;
    Camera camera;
    //SensorSet sensors;  //TODO: remove this if we don't have any charge sensor

    Bot();
    ~Bot();

    //Initialization
    void driveToMainLine();

    //Line-following
    void goToLineAndFollowItTo(Cylinder cyl, double distance);

    //Cylinder-Searching
    void pointTo(Cylinder cyl);
    PolarPoint searchFor(Cylinder cyl);
    void homeInOn(Cylinder, double distance);

    //Charging/Discharging
    void chargeFor(double time);
    void dischargeFor(double time);

    //Vel / RotVel interfacing
    double getVel();
    void   setVel(double vel);
    double getRotVel();
    void   setRotVel(double rotVel);

    // Moving fuctions (forwards/backwards)
    void move(bool direction, double distance);
    void moveForward(double distance);
    void moveBackward(double distance);
    void startMoving(bool direction, double speed);
    void startMovingForward(double speed);
    void startMovingBackward(double speed);
    void stopMoving();
    // Turning functions (rotate left/right)
    void turn(double inputAngle);
    void turn(bool direction, double inputAngle);
    void turnLeft(double inputAngle);
    void turnRight(double inputAngle);
    void startTurning(bool direction, double speed);
    void stopTurning();
};

#endif	//BOT_H
