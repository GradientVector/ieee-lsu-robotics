#include "Angle.h"

Angle::Angle(){
    angle = 0;
}

Angle::Angle(double in_angle){
    angle = setAngle(in_angle);
}

double Angle::getAngle() {
	return angle;
}

void Angle::setAngle(double newAngle) {
	while(newAngle < 0) {
		newAngle += 360;	
	}
	angle = newAngle % 360;
}
