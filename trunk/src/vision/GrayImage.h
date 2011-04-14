#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "../util/PixelPoint.h"

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
