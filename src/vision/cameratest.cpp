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
  if (argv == 1) cap >> img;
  while (cvWaitKey(10)!=27){
      if (argv == 1) cap >> img;
    //red = getRedPixels(img,150);
    imshow("ICECHEST", img);
    //imshow("BEER", red);
    sleep(1);
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
