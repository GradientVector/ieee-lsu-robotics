#include "PolarPoint.h"


PolarPoint::PolarPoint(double in_r, double in_th){
    r = in_r;
    th = in_th;
}

PolarPoint::PolarPoint(){
    r = 0.0;
    th = 0.0;
}

void PolarPoint::setPolarPoint(double in_r, double in_th){
    r = in_r;
    th = in_th;
}

void PolarPoint::setR(double toSet) {
    r = toSet;
}

double PolarPoint::getR() {
    return r;
}

void PolarPoint::setTh(double toSet) {
    th = toSet;
}

double PolarPoint::getTh() {
    return th;
}
