/**
loose functions for vision, not belonging to a class
 */

#ifndef _VISION_H_
#define _VISION_H_

#include <math.h>
#include "../util/util.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "../util/PixelPoint.h"
#include "../util/Cylinder.h"
#include "../util/PolarPoint.h"

using namespace std;
using namespace cv;

void grabLines(Mat &img, vector<Vec4i> &line);
void getMidLine(Point line1_pt1, Point line1_pt2, Point line2_pt1, Point line2_pt2, Point &mdpt1, Point &midpt2);
Point getMidpoint(Point pt1, Point pt2);
double getDistance(Point pt1, Point pt2);
PixelPoint findLine();
//#TODO: Need to update this header file, missing some functions

#endif
