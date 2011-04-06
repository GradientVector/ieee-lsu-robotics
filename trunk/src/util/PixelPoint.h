#ifndef PIXEL_POINT_H
#define PIXEL_POINT_H

//holds a location in an image; units are pixels.
//the origin is the upper lefthand side of the image.
class PixelPoint {
	public:
		int x;	//x pixel coordinate, defining x=0 to be the ?top? of image
		int y; 	//y pixel coordinate, defining y=0 to be the left of image
		PixelPoint(int ix, int iy);
		PixelPoint();
};

#endif
