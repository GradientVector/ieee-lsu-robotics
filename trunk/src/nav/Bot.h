#ifndef BOT_H
#define BOT_H

#include <math.h>
#include "../vision/vision.h"
//#include "../sensors/sensors.h"
#include "../util/util.h"
#include "../util/Angle.h"
#include "../util/PolarPoint.h"
#include "../util/Cylinder.h"
//p#include "../util/PhysicalLine.h"

//will only be instantiated once. represents the robot itself.
//Holds location and angle information.
class Bot {
    private:
    double velocity, rotVel;      //rotVel>0 means the bot is twisting left

    //accessors for each wheel speed due to each type of motion; returns value from -9999 to 9999 (mci scale)
    double getRSpeedDueToVel();
    double getLSpeedDueToVel();
    double getRSpeedDueToRotVel();
    double getLSpeedDueToRotVel();
	
	
    public:
    const double STD_STOP_DIST = 6;     //when navigating by homeInOn(-,-),  this is the standard stopping distance(inches) when we don't want to touch the object 
    const double TOUCH_DIST = 0;        //distance(inches) from our camera to the object when we are touching it
    const double WHL_DIAM;              //separation b/t the wheels
    const double WHL_RADIUS = WHL_DIAM/2;	

    //high speeds at which things start going wrong(i.e. slippage, popping wheelies, etc). Subj to change
    const double MAX_SPEED     = 25;    //inches/second
    const double MAX_ROT_SPEED = 400;	//degrees/second

    //good, standard speeds that aren't too fast/slow.
    const double COMFY_SPEED      = 0.5 * MAX_SPEED;		
    const double COMFY_TURN_SPEED = 0.5 * MAX_ROT_SPEED;

    const double IN_PER_SEC = 5;        //the speed, in in/sec, represented by passing "1,1" to the MCI's setVelocity() function; a simple unit conversion factor. TODO: value should be changed later
    const double DEG_PER_SEC = 5;       //the rotational speed, in deg/sec, represented by passing "-1,1" (TODO) to the MCI's setVelocity() function; a simple unit conversion factor. TODO: value should be changed later

    // Movement logic
    const bool LEFT = true;                 // Turning left uses positive velocity
    const bool RIGHT =  !LEFT;              // Turning right uses negative velocity
    const bool FORWARD = true;              // Moving forward uses positive velocity
	const bool BACKWARD =  !FORWARD;        // Moving backward uses negative velocity

    // Camera related variables
    const double VERTICAL_TILT_ANGLE = 90;   // 0 degrees is pointing perpendicular (straight at) the ground; 90 degrees is parallel to the ground
    const double CAMERA_HEIGHT = 6.3;          // Height (in inches) from ground.
    const double VERT_FIELD_ANGLE = 45;      // 56 deg or 75 deg, probably using 75 deg
    const double HORIZ_FIELD_ANGLE = 60;
    const int IMG_WIDTH_PX = 640;
    const int IMG_HEIGHT_PX =  480;

    SensorSet sensors;
    CartesianPoint location;
    Angle angle;
    MCI mci;

    Bot();
    ~Bot();

    //Initialization
    void driveToMainLine();

    //Line-following
    void goToLineAndFollowItTo(Cylinder cyl, double distance);

    //Cylinder-Searching
    void pointTo(Cylinder cyl);
    PixelPoint searchFor(Cylinder cyl);
    void homeInOn(Cylinder, double distance);

    //Charging/Discharging
    void chargeFor(double time);
    void dischargeFor(double time);

    //Vel / RotVel interfacing
    void getVel();
    void setVel(double vel);
    void getRotVel();
    void setRotVel(double rotVel);

    // Start move fuctions (forwards/backwards)
    void moveTo(bool direction, double distance, double speed);
    void startMoving(bool direction, double speed);
    void moveForwardTo(double distance, double speed);
    void moveBackwardTo(double distance, double speed);
    void startMovingForward(double speed);
    void startMovingBackward(double speed);
    void stopMoving();
    // Start turning functions (rotate left/right)
    void turnTo(double angle, double speed);
    void turnTo(Angle angle, double speed);
    void turn(bool direction, double angle, double speed);
    void turn(bool direction, Angle angle, double speed);
    void startTurning(bool direction, double speed);
    void turnLeft(double angle, double speed);
    void turnRight(double angle, double speed);
    void startTurningLeft(double speed);
    void startTurningRight(double speed);
    void stopTurning();
};

#endif	//BOT_H
