#include "Cylinder.h"

//This was added so that Map.cpp would compile; why do we need it? it's never 'used'.  -Andrew
Cylinder::Cylinder() {
    //intentionally blank
}

Cylinder::Cylinder(int colorPassed, CartesianPoint locationPassed) {
	color = colorPassed;
	location = locationPassed;
}
