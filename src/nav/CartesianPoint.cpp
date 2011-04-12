#include "CartesianPoint.h"

CartesianPoint::CartesianPoint(double xPassed, double yPassed) {
	x = xPassed;
	y = yPassed;
}

//TODO: this was created to help Cylinder.cpp compile; why do we need it?
CartesianPoint::CartesianPoint() {
    x = 0;
    y = 0;
}
