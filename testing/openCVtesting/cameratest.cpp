#include <iostream>
#include <vector>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <unistd.h>

using namespace std;
using namespace cv;

Mat getRedPixels(Mat src, unsigned char intensity);
void grabLines(Mat &img, vector<Vec4i> &line);

int main(int argv, char **argc) {
  Mat img,red;
  vector <Vec4i> lines;
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
  namedWindow("BEER",CV_WINDOW_NORMAL);
  namedWindow("ICECHEST",CV_WINDOW_NORMAL);
  cvResizeWindow("BEER",640,480);
  cvResizeWindow("ICECHEST",640,480);
  for (int i=0;i<50;i++) 
    if (argv == 1) cap >> img;
  while (cvWaitKey(10)!=27){
      if (argv == 1) cap >> img;
    red = getRedPixels(img,150);
    //grabLines(img,lines); 
    //for (unsigned int i=0;i<lines.size();i++)
    //  line( img, Point(lines[i][0],lines[i][1]), Point(lines[i][2],lines[i][3]), Scalar(255,0,0), 2, 8 );
    imshow("ICECHEST", img);
    imshow("BEER", red);
  }
  return 0;
}


Mat getRedPixels(Mat src, unsigned char intensity) {
  vector<Mat> planes;
  split(src,planes);
  Mat red(src.rows,src.cols,CV_8UC1);
  subtract(planes[2],planes[1],red);
  subtract(red,planes[0],red);
  return red;
}

void grabLines(Mat &img, vector<Vec4i> &line) {
    Mat gray;
    cvtColor(img,gray,CV_BGR2GRAY); 
    Canny(gray,gray,5,200);
    imshow("test",gray);
    HoughLinesP(gray,line,1,CV_PI/180,80,10,200);
    cout << "Line size: " << line.size() << endl;
    //if (line.size()<50 && line.size()>1) processLines(img,line);
}

