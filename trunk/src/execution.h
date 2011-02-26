/**
Filename:	execution.cpp

This, along with execution.cpp, will hold functionality for talking to our motor controllers.

Log:	2011 Feb 25 - document created by Andrew Elias

TODO list:
	

*/

#ifndef _EXECUTION_H_
#define _EXECUTION_H_

#include "vision.h"
using namespace std;

void setVel(double vel);

void setRotVel(double rotVel);

//will only be instantiated once. represents the robot itself.
//Holds location and angle information.
class Bot {
	public:
		CartesianPoint location;
		Angle angle;
};

#endif
