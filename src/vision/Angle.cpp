#include "Angle.h"

Angle::Angle(){
    angle = 0;
}

Angle::Angle(double in_angle){
    angle = in_angle;
}

double Angle::getAngle() {
	return angle;
}

void Angle::setAngle(double newAngle) {
	angle = newAngle % 360;
}
