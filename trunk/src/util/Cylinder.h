#ifndef CYLINDER_H
#define CYLINDER_H



class Cylinder {
	public:
	
	const int NOT_FOUND = 0; 
	const int RED       = 1;
	const int GREEN     = 2;
	const int BLUE      = 3;
	const int YELLOW    = 4;
	const int BLACK     = 5;

	CartesianPoint location;
	int color;
	Cylinder(int colorPassed, CartesianPoint locationPassed);
};

#endif
