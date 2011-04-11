/*
// OpenCV_Helloworld.cpp : Defines the entry point for the console application.
// Created for build/install tutorial, Microsoft Visual C++ 2010 Express and OpenCV 2.1.0

//#include "stdafx.h"

#include "opencv/cv.h"
//#include "opencv/cv.hpp"
//#include "opencv/cvaux.h"
//#include "opencv/cvaux.hpp"
//#include "opencv/cvwimage.h"
#include "opencv/cxcore.h"
//#include "opencv/cxcore.hpp"
//#include "opencv/cxeigen.hpp"
//#include "opencv/cxmisc.h"
#include "opencv/highgui.h"
//#include "opencv/ml.h"

int _tmain(int argc, _TCHAR* argv[])
{
        IplImage *img = cvLoadImage("funny-pictures-cat-goes-pew.jpg");
        cvNamedWindow("Image:",1);
        cvShowImage("Image:",img);

        cvWaitKey();
        cvDestroyWindow("Image:");
        cvReleaseImage(&img);

        return 0;
}*/

////////////////////////////////////////////////////////////////////////
//
// hello-world.cpp
//
// This is a simple, introductory OpenCV program. The program reads an
// image from a file, inverts it, and displays the result. 
//
////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"


int main(int argc, char *argv[])
{
  IplImage* img = 0; 
  int height,width,step,channels;
  uchar *data;
  int i,j,k;

  if(argc<2){
    printf("Usage: main <image-file-name>\n\7");
    exit(0);
  }

  // load an image  
  img=cvLoadImage(argv[1]);
  if(!img){
    printf("Could not load image file: %s\n",argv[1]);
    exit(0);
  }

  // get the image data
  height    = img->height;
  width     = img->width;
  step      = img->widthStep;
  channels  = img->nChannels;
  data      = (uchar *)img->imageData;
  printf("Processing a %dx%d image with %d channels\n",height,width,channels); 

  // create a window
  cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
  cvMoveWindow("mainWin", 100, 100);

  // invert the image
  for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++)
    data[i*step+j*channels+k]=255-data[i*step+j*channels+k];

  // show the image
  cvShowImage("mainWin", img );

  // wait for a key
  cvWaitKey(0);

  // release the image
  cvReleaseImage(&img );
  return 0;
}
