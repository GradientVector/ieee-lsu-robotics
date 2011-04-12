/**
loose vision functions not belonging to any particular class
 */

#ifndef _VISION_CPP_
#define _VISION_CPP_
#include <math.h>
#include "vision.h"
#include "../nav/navigation.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.14159265

//using namespace std; // #TODO: Remove this line - shouldn't define namespace in library file, only in actual executable.


PolarPoint placeObject(PixelPoint object) {

    double middle_x = Bot.IMG_WIDTH_PX/2;     // Coordinate for middle pixel on x axis
    double middle_y = IMG_HEIGHT_PX/2;    // Coordinate for middle pixel on y axis
    double diff_x;                        // Horizontal difference between camera middle pixel and object pixel
    double diff_y;                        // Vertical difference between camera middle pixel and object pixel
    Angle vertDiffAngle;                // Angle between middle of screen and vertical position of object, + = left of middle
    Angle horizDiffAngle;               // Angle between middle of screen and horizontal position of object, + = above middle
    Angle absVertAngle;                 // Object's angle relative to camera position on robot  #TODO: Rename variable
    double  distanceFromRobot;          // Distance between robot and object

    // find angle between robot's direction and object
    diff_x = (middle_x - object.x)/ middle_x;  // +middle_x = far left, -middle_x = far right
    horizDiffAngle.setAngle(diff_x * (HORIZ_FIELD_ANGLE/2));
   
    // calculate distance between robot and object
    diff_y = (middle_y - object.y)/middle_y;  // +middle_y = top, -middle_y = bottom
    vertDiffAngle.setAngle(diff_y * (VERT_FIELD_ANGLE/2));
    absVertAngle.setAngle(vertDiffAngle.getAngle() + VERTICAL_TILT_ANGLE);
    distanceFromRobot = fabs(CAMERA_HEIGHT * tan(absVertAngle.getAngle()*(PI/180)));  // based on trig function, same units as CAMERA_HEIGHT
    // #TODO: See if this works or if tan() needs to just be Math.tan()

    PolarPoint updated_position(distanceFromRobot , horizDiffAngle);
    
    return updated_position;
}


//finds a line on the screen
//returns the center of the line segment found. If the line on the screen goes from (300,10) to (200,50), the return value will be (250,30).  
PixelPoint findLine(){
  // #TODO Move most of this to Bot file to make more efficient
  int argv = 'g'
  char **argc = '02'
  Mat img;
  vector <Vec4i> lines;
  Point lineMidPt1, lineMidPt2;
  VideoCapture cap(0);
  //cap.set(CV_CAP_PROP_FPS,60);
  cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
  cap.set(CV_CAP_PROP_GAIN,0);
  if (argv > 1)
      img = imread(argc[1]);
  else {
      if (!cap.isOpened()) {
          cout << "Error opening video. Exiting" << endl;
          return -1;
      }
  }
  //namedWindow("Line View",CV_WINDOW_NORMAL);
  //cvResizeWindow("Line View",640,480);
  for (int i=0;i<50;i++)
    if (argv == 1) cap >> img;
  while (cvWaitKey(10)!=27){
    if (argv == 1) cap >> img;
    grabLines(img,lines);
    for (unsigned int i=0;i<lines.size();i++){
      line( img, Point(lines[i][0],lines[i][1]), Point(lines[i][2],lines[i][3]), Scalar(255,0,0), 2, 8 );
    }
    if (lines.size() == 2){
        getMidLine(Point(lines[0][0],lines[0][1]),Point(lines[0][2], lines[0][3]),Point(lines[1][0], lines[1][1]),Point(lines[1][2], lines[1][3]), lineMidPt1, lineMidPt2);
        line( img, lineMidPt1, lineMidPt2, Scalar(0,0,255), 2, 8 );
    }
    //imshow("Line View", img);
  }

    //TODO
    // given cylinder,
    // look towards cylinder
    // find cylinder, look for line going to it
    // if found,
    // check if on top of line
    // if not on line, rotate + look for shortest path to line (line is perpendicular to camera) (remember rotation direction)
    // once rotated to face shortest path, move to a point on the line
    // once on top of line, rotate back to look down line (use opposite rotation direction used above ^)
    // once looking down line, move forward while drawing a line between middle of edges + keep that line vertical.
    // Keep moving until line is no longer visible


}

void grabLines(Mat &img, vector<Vec4i> &line) {
    Mat gray;
    cvtColor(img,gray,CV_BGR2GRAY);
    threshold(gray, gray, 175, 255,cv::THRESH_BINARY);
    //imshow("pretest",gray);
    Canny(gray,gray,25,175);
    cv::Mat roi(gray, Rect(0,0,gray.cols,250));  // cut off top
    roi = Scalar(0,0,0);                         // cut off top
    //imshow("test",gray);
    HoughLinesP(gray,line,1,CV_PI/180,80,10,200);
    //cout << "Line size: " << line.size() << endl;
}

void getMidLine(Point line1_pt1, Point line1_pt2, Point line2_pt1, Point line2_pt2, Point &midpt1, Point &midpt2){
    double dist1 = getDistance(line1_pt1, line2_pt1);
    double dist2 = getDistance(line1_pt1, line2_pt2);
    if (dist1 <= dist2){
        midpt1 = getMidpoint(line1_pt1, line2_pt1);
        midpt2 = getMidpoint(line1_pt2, line2_pt2);
    } else {
        midpt1 = getMidpoint(line1_pt1, line2_pt2);
        midpt2 = getMidpoint(line1_pt2, line2_pt1);
    }
}

Point getMidpoint(Point pt1, Point pt2){
    Point midPoint;
    midPoint = Point(((pt1.x+pt2.x)/2),((pt1.y+pt2.y)/2));
    return midPoint;
}

double getDistance(Point pt1, Point pt2){
    double dist;
    dist= sqrt(pow((pt1.x - pt2.x),2) + pow((pt1.y - pt2.y),2));
    return dist;
}

//this returns a color at a point
int color(Mat img, int x, int y) {
	//TODO by John West
	int& temp = img.at<uchar>(y, x);
	return temp;
}

PixelPoint findObject(cyl) {
    int clrLmt = 225; //color intensity minimum
    Mat gryClr = grayImage.getGI(cyl.color);
    PixelPoint cylPt(0, 0);
    for(int i = 1; i <= viewWidth; i++)
    {
	if (i <= viewHeight)
	{
	    for (int j = i; j <= viewHeight; j++)
	        if (color(gryClr, i - j, viewHeight - i + j) >= clrLmt)
		    if (checkArea(i - j, viewHeight - i + j, gryClr, cylPt))
		        return cylPt;
	}
	else
	{
	    for (int j = 1; j <= viewHeight; j++)
		if (color(gryClr, i - viewHeight + j, j) >= clrLmt)
		    if (checkArea(i - viewHeight + j, j, gryClr, cylPt))
			return cylPt;
	}
    }
    for (int i = viewHeight; i >= 1; i--)
	for (int j = i; j >= 1; j--)
	    if (color(gryClr, i - j, j) >= clrLmt)
		if (checkArea(i - j, j, gryClr, cylPt))
		    return cylPt;
    return cylPt;
}

bool checkArea(int cx, int cy, Mat gry, Point &Pt)//checks the average number of pixels of the same color
{
    int clrLmt = 225;
    int total = 0;
    int cap = 65; //predicted average as a percentage, change by experimentation
    int clr = 0; //amount of pixels with this color
    int topB, bottomB, leftB, rightB, LB, RB;
    for (int yy = cy - camScale*cy*(cylHeight + 5); yy <= cy + 5; yy++)
	for (int xx = cx - 5; xx <= cx + camScale*cy*(cylWidth + 5); x++)
	    if (color(gry, xx, yy) >= 225)
	    {
		total++;
		clr++;
	    }
    if ((total * 100) / clr >= cap) //finds the center pixel and adds it to the list of objects, may require a top cap ~90
    {
	for (int yy = cy - camScale*cy*(cylHeight + 5); !bottomB && yy <= cy; yy++)
	    for (int xx = cx; xx <= !bottomB && cx + camScale*cylWidth*cy; x++)
		if (color(gry, xx, yy) >= clrLmt)
		    bottomB = yy;
	for (int xx = cx - 5; !leftB && xx <= cx + camScale*cylWidth*cy; xx++)
	    for (int yy = cy - camScale*cy*cylHeight; !leftB && yy <= cy; yy++)
		if (color(gry, xx, yy) >= clrLmt)
		    leftB = xx;
	for (int xx = cx + camScale*cy*(cylWidth + 5); !rightB && xx >= cx; xx--)
	    for (int yy = cy - camScale*cy*cylHeight; !rightB && yy <= cy; yy++)
		if (color(gry, xx, yy) >= clrLmt)
		    rightB = xx;
	Pt.x = (leftB + rightB)/2;
	for (int yy = bottomB; !LB && !RB && yy > bottomB + camScale*cylHeight*cy/2; y--)
	{
	    if (color(gry, cx + cylWidth*cy*camScale/4, bottomB) >= clrLmt || color(gry, cx + cylWidth*cy*camScale/4 + 1, bottomB) >= clrLmt || 
		color(gry, cx + cylWidth*cy*camScale/4 - 1, bottomB) >= clrLmt)
		LB = yy;
	    if (color(gry, cx + 3*cylWidth*cy*camScale/4, bottomB) >= clrLmt || color(gry, cx + 3*cylWidth*cy*camScale/4 + 1, bottomB) >= clrLmt || 
		color(gry, cx + 3*cylWidth*cy*camScale/4 - 1, bottomB) >= clrLmt)
		RB = yy;
	}
	if (LB && RB)
	    Pt.y = (LB + RB)/2;
	else
	    Pt.y = bottomB;
	return true;
    }
    else return false;
}


#endif
