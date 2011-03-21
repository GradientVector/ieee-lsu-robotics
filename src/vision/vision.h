/**
Filename:	vision.h

This, along with vision.cpp, contain all functionality necessary for using the camera.

LOG:
	2011 Feb 24 - blank document created by Andrew Elias

TODO notes:
	

 */

#ifndef _VISION_H_
#define _VISION_H_

using namespace std;

//holds a location in an image; units are pixels.
//the origin is the upper lefthand side of the image.
class PixelPoint {
	public:
		int x;	//x pixel coordinate, defining x=0 to be the ?top? of image
		int y; 	//y pixel coordinate, defining y=0 to be the left of image
		PixelPoint(int ix, int iy);
		PixelPoint();
};

class GrayImage
{
  public:
    Mat getGI(int color);
  private:
    Mat getRedPixels();
    Mat getBluePixels();
    Mat getYellowPixels();
    Mat getGreenPixels();
    Mat getLines();
    vector<Mat> planes;
};
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

/*
class Polar {
    private:
        double rho;
        double theta;
        complex<double> coord = polar(rho, theta);
    public:


};
 */


const int NOT_FOUND = 0; 
const int RED       = 1;
const int GREEN     = 2;
const int BLUE      = 3;
const int YELLOW    = 4;
const int BLACK     = 5;

const double VERTICAL_TILT_ANGLE = 90;   // 0 degrees is pointing perpendicular (straight at) the ground, 90 degrees is parallel to the ground
const double CAMERA_HEIGHT = 5;          // Height (in inches) from ground. Test value of 5 was randomly chosen.
const double VERT_FIELD_ANGLE = 45;      // 56 deg or 75 deg, probably using 75 deg
const double HORIZ_FIELD_ANGLE = 60;
const int IMG_WIDTH_PX = 640;
const int IMG_HEIGHT_PX =  480;
const double Y_SCALING_RATIO;            // How much stuff strinks while moving away


class Cylinder {
	public:
	static const int NOT_FOUND = 0; 
	static const int RED       = 1;
	static const int GREEN     = 2;
	static const int BLUE      = 3;
	static const int YELLOW    = 4;
	static const int BLACK     = 5;

	CartesianPoint location;
	int color;
	Cylinder(int colorPassed, CartesianPoint locationPassed);
};


//uses the image to find the pixel coordinates of the base of a cylinder (or line)
PixelPoint findObject(Cylinder cyl);

//converts the pixel coordinates to a real-life relative position
PolarPoint placeObject(PixelPoint);



#endif
