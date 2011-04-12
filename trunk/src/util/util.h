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


#endif  //for UTIL_H
