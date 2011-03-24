#include "PolarPoint.h"

PolarPoint::PolarPoint(double in_r, Angle in_th){
    r = in_r;
    th = in_th;
}
PolarPoint::PolarPoint(double in_r, double in_th){
    r = in_r;
    th.setAngle(in_th);
}

PolarPoint::PolarPoint(){
    r = 0.0;
    th.setAngle(0.0);
}
