#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <unistd.h>

using namespace std;
using namespace cv;

Mat getRedPixels(Mat src, unsigned char intensity);

int main(int argv, char **argc) {
  Mat img,red;
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
  //namedWindow("BEER",CV_WINDOW_NORMAL);
  namedWindow("ICECHEST",CV_WINDOW_NORMAL);
  //cvResizeWindow("BEER",640,480);
  cvResizeWindow("ICECHEST",640,480);
  for (int i=0;i<50;i++) 
    if (argv == 1) cap >> img;
  while (cvWaitKey(10)!=27){
      if (argv == 1) cap >> img;
    //red = getRedPixels(img,150);
    imshow("ICECHEST", img);
    //imshow("BEER", red);
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
