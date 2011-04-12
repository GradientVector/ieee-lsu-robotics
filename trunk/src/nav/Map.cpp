#include "Map.h"

Map::Map() {
	CartesianPoint bluePoint   = CartesianPoint(6, 90);
	CartesianPoint greenPoint  = CartesianPoint(90, 90);
	CartesianPoint redPoint    = CartesianPoint(72, 12);
	CartesianPoint yellowPoint = CartesianPoint(6, 6);

	blueCyl   = Cylinder(BLUE,   bluePoint);
	greenCyl  = Cylinder(GREEN,  greenPoint);
	redCyl    = Cylinder(RED,    redPoint);
	yellowCyl = Cylinder(YELLOW, yellowPoint);
}
