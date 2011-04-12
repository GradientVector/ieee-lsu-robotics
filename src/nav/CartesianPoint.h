#ifndef CARTESIAN_POINT_H
#define CARTESIAN_POINT_H

//holds a location on a map; units are inches.
//by convention the origin is the lower lefthand side of the map.
class CartesianPoint {
	public:
	double x;	//units: inches
				//x==0 indicates the bottom of the map
	double y;
				//y==0 indicates the left side of the map
    CartesianPoint();
	CartesianPoint(double xPassed, double yPassed);
};

#endif
