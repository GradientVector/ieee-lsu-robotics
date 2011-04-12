#include "Cylinder.h"

Cylinder::Cylinder(int colorPassed, CartesianPoint locationPassed) {
	color = colorPassed;
	location = locationPassed;

    NOT_FOUND = 0;
    RED = 1;
    GREEN = 2;
    BLUE = 3;
    YELLOW = 4;
    BLACK = 5;
}
