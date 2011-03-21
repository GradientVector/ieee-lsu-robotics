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
};


const int NOT_FOUND = 0; 
const int RED       = 1;
const int GREEN     = 2;
const int BLUE      = 3;
const int YELLOW    = 4;
const int BLACK     = 5;

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
PolarPosition placeObject(PixelPoint);



#endif
