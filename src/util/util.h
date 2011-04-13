/*
	loose utility functions
*/
#ifndef UTIL_H
#define UTIL_H


//#include <unistd.h>
//#include <cstdlib>
//#include <stdlib.h>
//#include <ctime>  //may be necessary if we change the wait() function later
#include <time.h>

void wait(unsigned int milliseconds);

const double PI = 3.1415926;
const double RADIANS_PER_DEGREE = PI / 180;
const double DEGREES_PER_RADIAN = 180 / PI;

const int NOT_FOUND  = 0;
const int RED        = 1;
const int GREEN      = 2;
const int BLUE       = 3;
const int YELLOW     = 4;
const int BLACK      = 5;

// Movement logic
const bool LEFT = true;                 // Turning left uses positive velocity
const bool RIGHT =  !LEFT;              // Turning right uses negative velocity
const bool FORWARD = true;              // Moving forward uses positive velocity
const bool BACKWARD =  !FORWARD;        // Moving backward uses negative velocity


#endif  //for UTIL_H
