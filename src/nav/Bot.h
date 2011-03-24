#ifndef BOT_H
#define BOT_H

#include <math.h>

//will only be instantiated once. represents the robot itself.
//Holds location and angle information.
class Bot {
	private:
	double velocity, rotVel;
	
	public:
	const double STD_STOP_DIST = 6; 	//when navigating by homeInOn(-,-),  this is the standard stopping distance(inches) when we don't want to touch the object 
	const double TOUCH_DIST = 0;		//distance(inches) from our camera to the object when we are touching it
	const double WHL_DIAM;			//separation b/t the wheels
	
	//high speeds at which things start going wrong. (temp; subj to change)
	const double MAX_SPEED = 10;		//inches/second
	const double MAX_ROT_SPEED = 720;	//degrees/second
	//good, standard speeds that aren't too fast/slow. on a scale from -1 to 1, where 1 is MAX_SPEED
	const double COMFY_SPEED = 0.5;		
	const double COMFY_TURN_SPEED = 0.5;
	
	const double VERTICAL_TILT_ANGLE = 90;   // 0 degrees is pointing perpendicular (straight at) the ground, 90 degrees is parallel to the ground
	const double CAMERA_HEIGHT = 5;          // Height (in inches) from ground. Test value of 5 was randomly chosen.
	const double VERT_FIELD_ANGLE = 45;      // 56 deg or 75 deg, probably using 75 deg
	const double HORIZ_FIELD_ANGLE = 60;
	const int IMG_WIDTH_PX = 640;
	const int IMG_HEIGHT_PX =  480;

	SensorSet sensors;
	CartesianPoint location;
	Angle angle;
	MCI mci;

	void driveToMainLine();
	void followLineTo(Cylinder cyl, double distance);
	void pointTo(Cylinder cyl);
	void homeInOn(Cylinder, double distance);
	void chargeFor(/*TODO*/);
	void dischargeFor(/*TODO*/);
	void getVel();
	void setVel(double vel);
	void getRotVel();
	void setRotVel(double rotVel);
};

#endif	//BOT_H
