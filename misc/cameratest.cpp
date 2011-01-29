#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

struct _rgb {
  unsigned char b,g,r;
  _rgb(int r, int g, int b) : r(r), g(g), b(b) {}
};

IplImage *getRedPixels(IplImage *src, unsigned char intensity);

int main() {
  char c;
  int X=100,Y=100;
  _rgb *pixel;
  cvNamedWindow("BEER");
  cvNamedWindow("ICECHEST");
  CvCapture *capture= cvCaptureFromCAM(0);
  IplImage *img = cvQueryFrame(capture);
  img = cvQueryFrame(capture);
  IplImage *rd = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
  img = cvQueryFrame(capture);
  while (cvWaitKey(10)!=27){
    img = cvQueryFrame(capture);
    rd = img;
    getRedPixels(rd,150);
    pixel = (_rgb*)img->imageData + Y*img->width + X;
    printf("RGB = %d:%d:%d\n",pixel->r,pixel->g,pixel->b);
    cvShowImage("ICECHEST", img);
    cvShowImage("BEER", rd);
  }
//  cvReleaseImage(&img);
//  cvReleaseImage(&rd);
  cvReleaseCapture(&capture);
  cvDestroyWindow("BEER");
  cvDestroyWindow("ICECHEST");
  return 0;
}


IplImage *getRedPixels(IplImage *src, unsigned char intensity) {
  _rgb *pixel;
  _rgb black(0,0,0);
  _rgb red(255,0,0);
  for (int i=0;i<src->height;i++) {
    for (int j=0;j<src->width;j++) { 
      pixel = (_rgb*)src->imageData + j + i*src->width;
      float ratioA = pixel->r/(pixel->g+1);
      float ratioB = pixel->r/(pixel->b+1);
      if (ratioA < 2 || ratioB < 2) {
        *pixel = black;  
      }
      else
        *pixel = red;
    }
  }
  return src;
}
