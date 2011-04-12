#ifndef CYLINDER_H
#define CYLINDER_H

#include "../nav/CartesianPoint.h"

class Cylinder {
	public:
	
    //for some reason these can't be delared&initialized as const here; they are initialized in the constructor
    int NOT_FOUND;
	int RED;
	int GREEN;
	int BLUE;
	int YELLOW;
	int BLACK;

	CartesianPoint location;
	int color;
	Cylinder(int colorPassed, CartesianPoint locationPassed);
};

#endif
