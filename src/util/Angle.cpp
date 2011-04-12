#include "Angle.h"

Angle::Angle(){
    angle = 0;
}

Angle::Angle(double in_angle){
    setAngle(in_angle);
}

double Angle::getAngle() {
	return angle;
}

void Angle::setAngle(double newAngle) {
    //make sure the new angle is nonnegative so that the modulus operator is more predictable	
    while(newAngle < 0) {
		newAngle += 360;	
	}

    //make sure the new angle is less than 360 (modulus operator was giving me issues -Andrew)
    while(newAngle > 360) {
        newAngle -= 360;
    }
}
