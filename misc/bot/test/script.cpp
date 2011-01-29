#include <qbytearray.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qdesktopwidget.h>

#include <cv.h>
#include <highgui.h>

#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <unistd.h>
#include "XInput.h"

#define PLANETS 12 //planets in system + 1
int PLANET_LIST[] = {1,3,4,5,9,11}; //List of planets to check out
#define P_LIST_SIZE 6 //size of list
#define MATCH .6 //Returns what is ok for a match
#define MAX_POINTS 20 //# of max points returned from grabCircles
string chars[] = {"rash","butt"};
#define CHAR_NUM 2

//Resolution
#define HEIGHT 1080 //Desired height
#define WIDTH 1920 //Desired width

#define MIN_THRESHOLD 130 //For getting circles

#define NEUTRAL_X 1300 //Free clickable area
#define NEUTRAL_Y 300 //Free clickable area


using namespace cv;
using namespace std;

void login(Mat &img,const char *name); //logs in %s
//void password(); //Types password...needs to be encrypted
void screenCap(Mat &img);  //Captures image from screen
void screenDiff(Mat &img,Mat &diff);
//Clicks shit on your planet
//void doPlanetShit();
//Returns points, which should be your mines
//void grabCircles(Mat img, vector<Vec2i> pt,);
char* convert2Text(Mat &img, Rect rect);
void grabLines(Mat &img, Mat &diff, vector<Vec4i> &line);
float pdistance(Point a, Point b);
void processLines(Mat &img, vector<Vec4i> &line);

XInput sc;

int main(int argc, char *argv[]) {
	QApplication app(argc,argv);
    char *s;
    vector<Vec4i> lines;
    Mat img(HEIGHT,WIDTH,CV_8UC4);
    Mat diff(HEIGHT,WIDTH,CV_8UC4);
    Mat gray(HEIGHT,WIDTH,CV_8UC1); 

    namedWindow("test",CV_WINDOW_NORMAL);
    cvResizeWindow("test",1280,720);
	cvMoveWindow("test",2000,200);

    screenCap(img);
    //imshow("test",img);
    //waitKey(0);

    //Mat bob = imread("wat.png");
    //Rect rect(0,0,bob.cols,bob.rows);
    //s = convert2Text(bob,rect);
    //std::cout << s << std::endl;



    while(waitKey(100)!=27) {
        grabLines(img,diff,lines);
        for (int i=0;i<lines.size();i++)
            line( img, Point(lines[i][0],lines[i][1]), Point(lines[i][2],lines[i][3]), Scalar(255,255,255), 2, 8 );
        imshow("test",img);
        screenCap(img);
    }
	return 0;
}

char* convert2Text(Mat &img, Rect rect) {
    static char s[255];
    Mat temp((rect.width-rect.x)*2,(rect.height-rect.y)*2,img.flags);
    Mat temp2((rect.width-rect.x)*4,(rect.height-rect.y)*4,img.flags);
    Mat roi = img(rect);
    pyrUp(roi,temp);
    pyrUp(temp,temp2);
    imwrite("text.tiff",temp2);
    system("tesseract text.tiff text");
    std::ifstream tx("text.txt",ifstream::in);
    tx.read(s,255);
    tx.close();
    return s;
}
/*
void doPlanetShit(IplImage *img) {
    int num; //of points
    int bad = 0;
    double match[2];
    CvPoint *points[MAX_POINTS];
    CvPoint *pt[2];
    static IplImage *mine = cvLoadImage("images/minebuttons.png",0); //mine tab
    static IplImage *space = cvLoadImage("images/spacebuttons.png",0); //spaceport tab
    //static IplImage *install = cvLoadImage("images/install.png",0); //install button
    static IplImage *submit = cvLoadImage("images/submit.png",0); //submit button
    IplImage *gray = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,1);

    grabCircles(img,points,num);
        for (int i=0;i<num;i++) {
            sc.mouseMove(points[i]->x,points[i]->y);
            sc.mouseClick(1);
            sleep(1);
            img = screenCap(img);
            cvCvtColor(img,gray,CV_BGR2GRAY);
            pt[0] = scanTemplate(gray,space,match[0]);
            pt[1] = scanTemplate(gray,mine,match[1]);
            if (match[1] > match[0] ) {
                //printf("Matching %d\n",i);
                sc.mouseMove(pt[1]->x+35,pt[1]->y+25);
                sc.mouseClick(1);
                usleep(2500000);
                sc.mouseMove(pt[1]->x+175,pt[1]->y+135);
                sc.mouseClick(1);
                sleep(1);
                sc.mouseMove(pt[1]->x+165,pt[1]->y+250);
                sc.mouseClick(1);
                sleep(1);
            }
            else bad++;
            sc.mouseMove(1400,300);
            sc.mouseClick(1);
            sleep(1);
            delete pt[0];
            delete pt[1];
        }
    
        pt[0] = scanTemplate(gray,submit,match[0]);
        if (match[0] > .6) {
            sc.mouseMove(pt[0]->x+15,pt[0]->y+15);
            sc.mouseClick(1);
        }


        delete pt[0];
        for (int i=0;i<num;i++) delete points[i];
        cvReleaseImage(&gray);
}
    *//*
void grabCircles(IplImage *butts, CvPoint *points[20], int &num) { 
    char s[40];
    static int x=0;
    float *p;
    unsigned char* ptr;
    int16_t *pt;
    CvPoint bob;

    sleep(1);
    num = 0;
    butts = screenCap(butts);
    ptr = (unsigned char*) butts->imageData; 
    static IplImage *gray = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,1);
    static IplImage *boost = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_16S,1);
    CvMemStorage *storage = cvCreateMemStorage(0);
    
        //[B][G][R]  This subtracs the red from the green channel, then stores
        //the green in the 'gray' image
        for (int y=0;y<WIDTH*HEIGHT;y++){
            if (ptr[0] > ptr[2])
                gray->imageData[y] = max((unsigned char)(ptr)[1] - (unsigned char)(ptr[2]),0);
            else 
                gray->imageData[y] = 0;
            ptr+=4;
        }
    
        cvThreshold(gray,gray,MIN_THRESHOLD,255,CV_THRESH_BINARY);
        cvLaplace(gray,boost);
    
        pt = (int16_t*)boost->imageData ;
        for (int i=0;i<butts->height*butts->width;i++)
            gray->imageData[i] = (char)((pt++)[0]>>8);
    
        cvDilate(gray,gray);
        CvSeq *circles = cvHoughCircles(gray,storage,CV_HOUGH_GRADIENT,3,30,60,120,15,50);
        int length = min(circles->total,20);
        for (int i=0;i<circles->total;i++) {
            p = (float*)cvGetSeqElem(circles,i);
            bob.x = cvRound(p[0]); bob.y = cvRound(p[1]);
            cvCircle(butts,bob, 20, CV_RGB(255,0,0), 6);
            if (bob.x<1700) 
               points[num++] = new CvPoint(bob);
        }

        sprintf(s,"images/debug/bw%02d.png",x);
        cvSaveImage(s,gray);
        sprintf(s,"images/debug/circles%02d.png",x++);
        cvSaveImage(s,butts);
        cvReleaseMemStorage(&storage);
    return;
}
*/

float pdistance(Point a, Point b) {
    return pow(pow(a.x-b.x,2)+pow(a.y-b.y,2),.5);
}


void processLines(Mat &img, vector<Vec4i> &lines) {
    //Group first based upon distance between endpoints
    //Secondly, can group based on distance between either x or y values
    //Each point will have data based upon how many primary and secondary links
    //if if has primary link, should be an outer box
    //if a secondary, probably an inner box
    uchar *primary = new uchar[lines.size()];
    uchar *secondary = new uchar[lines.size()];
    for (int i=0;i<lines.size();i++)  
        primary[i] = secondary[i] = 0; 
    for (int i=0;i<lines.size();i++) {
        for (int j=i;j<lines.size();j++) {
            for (int k=0;k<4;k+=2) {
                for (int l=0;l<4;l+=2) {
                    if (pdistance(Point(lines[i][j],lines[i][j+1]),Point(lines[k][l],lines[k][l+1])) < 2) {
                        primary[i]++;
                        primary[j]++;
                    }
                    else if (abs(lines[i][j]-lines[k][l]) < 2 || abs(lines[i][j+1]-lines[k][l+1]) < 2) {
                        secondary[i]++;
                        secondary[j]++;
                    }
                }
            }
        }
    }

   delete primary;
   delete secondary;
}


//End goal: run this asyncrhonusly in the background
//and have an event when shit happens
void grabLines(Mat &img, Mat &diff, vector<Vec4i> &line) {
    Mat gray;
    screenDiff(img,diff);
    cvtColor(diff,gray,CV_BGR2GRAY); 
    Canny(gray,gray,5,200);
    //imshow("test",gray);
    HoughLinesP(gray,line,1,CV_PI/2,200,50,200);
    //if (line.size()<50 && line.size()>1) processLines(img,line);
}


void screenDiff(Mat &img,Mat &diff) { //Returns unaltered img
    Mat mask(img.rows,img.cols,CV_8UC1);
    Mat prev;
    img.copyTo(prev);
    screenCap(img); //get new image
    subtract(img,prev,diff);
    //diff now has what needs not to be subtracted
    cvtColor(diff,mask,CV_BGR2GRAY);
    //invert the mask and threshold to 255
    threshold(mask,mask,40,255,CV_THRESH_BINARY_INV);
    //subtract again, but with a mask
    subtract(img,prev,diff,mask);
}

void  screenCap(Mat &img) { 
  	QImage image = QPixmap::grabWindow(QApplication::desktop()->winId()).toImage().copy(0,0,WIDTH,HEIGHT);
    memcpy(img.data,image.bits(),image.byteCount());
}

void password() { //don't forget your shifts and ctrls
    sc.keyPress('',XK_Shift_L);
    sc.keyPress('');
    sc.keyPress('');
    sc.keyPress('');
    sc.keyPress('');
    sc.keyPress('');
    sc.keyPress('');
    sc.keyPress('');
    sc.keyPress(XK_Return);
}

void login(Mat &img, const char *name) {


    system("eve");

    password();
    
}


