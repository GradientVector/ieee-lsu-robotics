#ifndef CYLINDER_H
#define CYLINDER_H

#include "../nav/CartesianPoint.h"
#include "../util/util.h"

class Cylinder {
	public:
	
    //F it; color constants are gonna be declared in util.h/cpp

	CartesianPoint location;
	int color;
    Cylinder();
	Cylinder(int colorPassed, CartesianPoint locationPassed);
};

#endif
