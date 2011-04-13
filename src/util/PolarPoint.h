#ifndef POLAR_POINT_H
#define POLAR_POINT_H


//will be used to hold a relative position, in polar coordinates.
//This will help us know what angle we need to turn to face an object.
class PolarPoint {
	public:
    //TODO: make r, th private
	double r;	//radial  coordinate. units: inches
			//r==0 indicates our (the robot's) position
    void   setR(double toSet);
    double getR();

	double th;	//angular coordinate. units: degrees
			//th==0 indicates directly ahead of us
			//note: 'th' indicates 'theta'
    void   setTh(double toSet);
    double getTh();

    PolarPoint(double in_r, double in_th);
    PolarPoint();
    void setPolarPoint(double in_r, double in_th);
};

#endif
