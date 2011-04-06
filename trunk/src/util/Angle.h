#ifndef ANGLE_H
#define ANGLE_H

//holds an absolute direction. the value is protected, so that it never leaves the range 0-360 (degrees).
//0 degrees is defined to be in the direction of the map's positive x axis (pointing to the right/east). 
class Angle {
	private:
	double angle; 	//holds values from 0 to 360

	public:
	double getAngle();
	void setAngle(double newAngle);
                Angle();
                Angle(double in_angle);
};

#endif
