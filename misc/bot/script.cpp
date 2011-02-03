//guys: we need to start putting documentation on our source files. This file, for example, needs a header with a purpose and an author tag.
//Also, the filename gives no information about what this file does. Presumably it's a testing file, but that needs to be stated somewhere.
//sincerely, AndrewE

#include <qbytearray.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qdesktopwidget.h>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <algorithm>
#include "XInput.h"

#define PLANETS 12 //planets in system + 1
int PLANET_LIST[] = {1,3,4,5,9,11}; //List of planets to check out
#define P_LIST_SIZE 6 //size of list
#define MATCH .6 //Returns what is ok for a match
#define MAX_POINTS 20 //# of max points returned from grabCircles
const char *chars[] = {"rash","butt"};
#define CHAR_NUM 2

//Resolution
#define HEIGHT 1080 //Desired height
#define WIDTH 1920 //Desired width

#define MIN_THRESHOLD 130 //For getting circles

#define NEUTRAL_X 1300 //Free clickable area
#define NEUTRAL_Y 300 //Free clickable area

int login(IplImage *img,const char *name); //logs in %s
void password(); //Types password...needs to be encrypted
IplImage* screenCap(IplImage *img);  //Captures image from screen
IplImage* q2Image(QImage& qImage,IplImage *img); //Converts qImage to IPL
//Scans gray for temp, returns point and updates match
CvPoint* scanTemplate(IplImage* gray, IplImage *temp, double&match); 
//Same as above, but will wait for a value of MATCH
CvPoint *waitFor(IplImage *img,IplImage *temp,CvPoint *pt,int loop);
//Clicks shit on your planet
void doPlanetShit(IplImage *img);
//Returns points, which should be your mines
void grabCircles(IplImage *img, CvPoint* pt[MAX_POINTS], int &num);

FILE *f;
XInput sc;

int main(int argc, char *argv[]) {
	QApplication app(argc,argv);
    //cvNamedWindow("test",0);
    //cvResizeWindow("test",1280,720);
	//cvMoveWindow("test",2000,200);
    
    int num;
    double match[2] = {0,0}; //match for overview and select
    CvPoint *pts[2]; //Overview and item select
    CvPoint *plts[PLANETS]; //planets points on overview, 0 is the Planet mode button
    IplImage *img = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,4); 
    IplImage *gray = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,1);
    IplImage *planet[PLANETS];

    IplImage *item = cvLoadImage("images/item.png",0);
    IplImage *overview = cvLoadImage("images/overview.png",0);
    planet[0] = cvLoadImage("images/select.png",0);
    f = fopen("log.txt","a");
    fprintf(f,"\n\n\nStarting Planetary Interaction run.\n");
    //Wake up monitor
/*    try {
        sc.mouseMove(WIDTH*.9,HEIGHT*.1);
        sleep(5);
        sc.mouseMove(WIDTH*.8,HEIGHT*.2);
        sleep(5);
        sc.mouseClick(1);
        sleep(5);
    }
    catch (exception& e) {
        fprintf(f,"Failed at startup.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
	//img = screenCap(img);
  */ 
    try {//Login
        if (login(img,"rash")!=0) {
            system("killall ExeFile.exe");
            if (login(img,"rash")!=0) {
                system("killall ExeFile.exe");
                return 0;
            }
        }
    }
    catch (exception& e) {
        fprintf(f,"Failed at login\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");
    sleep(5);

    try { //load all planet overview images
        char c[50];
        for (int i=0;i<P_LIST_SIZE;i++) {
            sprintf(c,"images/planets/planet%d.png",PLANET_LIST[i]);
            planet[PLANET_LIST[i]] = cvLoadImage(c,0);
        }
    	img = screenCap(img);
        cvCvtColor(img,gray,CV_BGR2GRAY);
    }
    catch (exception& e) {
        fprintf(f,"Failed at screencap.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        while(match[0] < .6 && match[1] < .6) { //find overview and item select
            pts[0] = scanTemplate(gray,overview,match[0]);
            pts[1] = scanTemplate(gray,item,match[1]);
            //cvCircle(img,*pt,5,CV_RGB(0,255,0),3);
            //cvCircle(img,*pt,5,CV_RGB(255,0,0),3);
            //cvShowImage("test",img);
            //cvWaitKey(20);
            img = screenCap(img);
            cvCvtColor(img,gray,CV_BGR2GRAY);
        }
    }
    catch (exception& e) {
        fprintf(f,"Failed at overview match.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {    
        //Click 'IP' tab
        sc.mouseMove(pts[0]->x+150,pts[0]->y+20);
        sc.mouseClick(1);
        sleep(2);
        img = screenCap(img);
        cvCvtColor(img,gray,CV_BGR2GRAY);
    
        //Find and click first planet
        plts[1] = scanTemplate(gray,planet[1],match[0]); 
        sc.mouseMove(plts[1]->x+10,plts[1]->y+10);
        sc.mouseClick(1);
    }
    catch (exception& e) {
        fprintf(f,"Failed loading clicking Planet 1.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        //Once loaded, find and click the 'Planet Mode' button
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[0] = scanTemplate(gray,planet[0],match[0]);
        plts[0]->x+=65; //Moves the template over so it clicks
        plts[0]->y+=10; //The actual Planet Mode button
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        //After a few seconds, scroll to the base
        sc.mouseDrag(1300,200,1300,300,1);
        sc.mouseDrag(1300,200,1300,300,1);
        sc.mouseDrag(1300,200,1300,300,1);
        fprintf(f,"P1 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 1.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        //Find planet 3's base
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[3] = scanTemplate(gray,planet[3],match[0]); 
        sc.mouseMove(plts[3]->x+10,plts[3]->y+10);
        sc.mouseClick(1);
        sleep(1);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        sc.mouseDrag(1300,300,1300,200,1);
        sc.mouseDrag(1300,300,1300,200,1);
        fprintf(f,"P3 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 3%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");


    try {
        //Find planets 4's base
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[4] = scanTemplate(gray,planet[4],match[0]); 
        sc.mouseMove(plts[4]->x+10,plts[4]->y+10);
        sc.mouseClick(1);
        sleep(1);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        for (int i=0;i<7;i++) sc.mouseDrag(1200,200,1200,400,1);
        for (int i=0;i<12;i++) sc.mouseDrag(1200,300,1400,300,1);
        fprintf(f,"P4 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 4.%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");


    try {
        //Find planet 11's base
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[11] = scanTemplate(gray,planet[11],match[0]); 
        sc.mouseMove(plts[11]->x+10,plts[11]->y+10);
        sc.mouseClick(1);
        sleep(1);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        sc.mouseDrag(1300,300,1200,200,1);
        sc.mouseDrag(1300,300,1200,200,1);
        sc.mouseDrag(1300,300,1200,200,1);
        fprintf(f,"P11 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 11.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");


    try {
        //Find planet 5's base
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[5] = scanTemplate(gray,planet[5],match[0]); 
        sc.mouseMove(plts[5]->x+10,plts[5]->y+10);
        sc.mouseClick(1);
        sleep(1);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        for (int i=0;i<6;i++) sc.mouseDrag(1400,200,1200,400,1);
        fprintf(f,"P5 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 5.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");


    //Exit planet mode
    try {
        sleep(3);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(2);
        system("killall ExeFile.exe");
    }
    catch (exception& e) {
        fprintf(f,"Failed Exiting EVE...?\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        if (login(img,"butt")!=0) {
            system("killall ExeFile.exe");
            if (login(img,"butt")!=0) {
                system("killall ExeFile.exe");
                return 0;
            }
        }
    }
    catch (exception& e) {
        fprintf(f,"Failed logging in Butt.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    sleep(5);
    try { //load all planet overview images
        char c[50];
        for (int i=0;i<P_LIST_SIZE;i++) {
            sprintf(c,"images/planets/planet%d.png",PLANET_LIST[i]);
            planet[PLANET_LIST[i]] = cvLoadImage(c,0);
        }
    	img = screenCap(img);
        cvCvtColor(img,gray,CV_BGR2GRAY);
    }
    catch (exception& e) {
        fprintf(f,"Failed at screencap.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");
    
    match[0] = match[1] = 0;
    try {
        while(match[0] < .6 && match[1] < .6) { //find overview and item select
            pts[0] = scanTemplate(gray,overview,match[0]);
            pts[1] = scanTemplate(gray,item,match[1]);
            //cvCircle(img,*pt,5,CV_RGB(0,255,0),3);
            //cvCircle(img,*pt,5,CV_RGB(255,0,0),3);
            //cvShowImage("test",img);
            //cvWaitKey(20);
            img = screenCap(img);
            cvCvtColor(img,gray,CV_BGR2GRAY);
        }
    }
    catch (exception& e) {
        fprintf(f,"Failed at overview match.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {    
        //Click 'IP' tab
        sc.mouseMove(pts[0]->x+150,pts[0]->y+20);
        sc.mouseClick(1);
        sleep(2);
        img = screenCap(img);
        cvCvtColor(img,gray,CV_BGR2GRAY);
    
        //Find and click first planet
        plts[1] = scanTemplate(gray,planet[1],match[0]); 
        sc.mouseMove(plts[1]->x+10,plts[1]->y+10);
        sc.mouseClick(1);
    }
    catch (exception& e) {
        fprintf(f,"Failed loading clicking Planet 1.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        //Once loaded, find and click the 'Planet Mode' button
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[0] = scanTemplate(gray,planet[0],match[0]);
        plts[0]->x+=65; //Moves the template over so it clicks
        plts[0]->y+=10; //The actual Planet Mode button
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        fprintf(f,"P1 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 1.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        //Find planets 4's base
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[4] = scanTemplate(gray,planet[4],match[0]); 
        sc.mouseMove(plts[4]->x+10,plts[4]->y+10);
        sc.mouseClick(1);
        sleep(1);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        fprintf(f,"P4 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 4.%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        //Find planet 5's base
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[5] = scanTemplate(gray,planet[5],match[0]); 
        sc.mouseMove(plts[5]->x+10,plts[5]->y+10);
        sc.mouseClick(1);
        sleep(1);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        for (int i=0;i<2;i++) sc.mouseDrag(1400,300,1200,300,1);
        fprintf(f,"P5 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 5.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        //Find planet 9's base
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[9] = scanTemplate(gray,planet[9],match[0]); 
        sc.mouseMove(plts[9]->x+10,plts[9]->y+10);
        sc.mouseClick(1);
        sleep(1);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        fprintf(f,"P9 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 9.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        //Find planet 11's base
        sleep(3);
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        plts[11] = scanTemplate(gray,planet[11],match[0]); 
        sc.mouseMove(plts[11]->x+10,plts[11]->y+10);
        sc.mouseClick(1);
        sleep(1);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(6);
        fprintf(f,"P11 has: ");
        doPlanetShit(img);
    }
    catch (exception& e) {
        fprintf(f,"Failed at Planet 11.\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");

    //Exit planet mode
    try {
        sleep(3);
        sc.mouseMove(plts[0]->x,plts[0]->y);
        sc.mouseClick(1);
        sleep(2);
        system("killall ExeFile.exe");
    }
    catch (exception& e) {
        fprintf(f,"Failed Exiting EVE...?\n%s.\n",e.what());
        fclose(f);
        return -1;
    }
    fclose(f);
    f = fopen("log.txt","a");
    

	return 0;
}

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
                printf("Matching %d\n",i);
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
        fprintf(f,"%d points, %d were bad.\n",num,bad);
        for (int i=0;i<num;i++) fprintf(f,"(%d,%d) ",points[i]->x,points[i]->y);
        fprintf(f,"\n");
    
        pt[0] = scanTemplate(gray,submit,match[0]);
        if (match[0] > .6) {
            sc.mouseMove(pt[0]->x+15,pt[0]->y+15);
            sc.mouseClick(1);
            fprintf(f,"Changes submited.\n");
        }


        delete pt[0];
        for (int i=0;i<num;i++) delete points[i];
        cvReleaseImage(&gray);
}
    
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

IplImage* screenCap(IplImage *img) { 
  	QImage image = QPixmap::grabWindow(QApplication::desktop()->winId()).toImage().copy(0,0,WIDTH,HEIGHT);
    return q2Image(image,img);
}

IplImage* q2Image(QImage& qImage,IplImage *img) { 
    static unsigned char* newdata = NULL;
    if (newdata != NULL) delete newdata;
    newdata = new unsigned char[qImage.byteCount()];
    memcpy(newdata,qImage.bits(),qImage.byteCount());
    img->imageData = (char*) newdata;
    return img;
}

CvPoint* scanTemplate(IplImage* gray, IplImage *temp,double&match) { //Allocates a point
    double minV,maxV;
    CvPoint minPt,maxPt;

    try {
    	IplImage *result = cvCreateImage(cvSize(WIDTH-temp->width+1,HEIGHT-temp->height+1),IPL_DEPTH_32F,1);
        cvMatchTemplate(gray,temp,result,CV_TM_CCOEFF_NORMED);
        cvMinMaxLoc(result,&minV,&maxV,&minPt,&maxPt);
        match = maxV;
        CvPoint *x = new CvPoint();
        x->x = maxPt.x; x->y = maxPt.y;
        cvReleaseImage(&result);
        return x;
    }
    catch (exception& e) {
        fprintf(f,"Failed scanning template.\n%s.\n",e.what());
        fclose(f);
        throw(e);
    }
    fclose(f);
    f = fopen("log.txt","a");
    return NULL;
}

CvPoint *waitFor(IplImage *img,IplImage *temp,CvPoint *pt,int loops=80) {
    double match = 0;
    static IplImage *gray = cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,1);
    try {
        img = screenCap(img); 
        cvCvtColor(img,gray,CV_BGR2GRAY);
        for (int i=0;i<loops;i++) {
            delete pt;
            pt = scanTemplate(gray,temp,match);
            img = screenCap(img); 
            cvCvtColor(img,gray,CV_BGR2GRAY);
            if (match>.6) 
                return pt;
            usleep(100000);
        }
        return NULL;
    }
    catch (exception& e) {
        fprintf(f,"Failed scanning template.\n%s.\n",e.what());
        fclose(f);
        throw(e);
    }
    fclose(f);
    f = fopen("log.txt","a");
    return NULL;
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

int login(IplImage *img, const char *name) {
    double match = 0;
    char s[50];
    CvPoint *pt = NULL;
    IplImage *small;
    IplImage *big;
    IplImage *login = cvLoadImage("images/login.png",0);
    try {
        sprintf(s,"images/chars/%s_small.png",name);
        small = cvLoadImage(s,0);
        sprintf(s,"images/chars/%s_big.png",name);
        big = cvLoadImage(s,0);

        system("eve");
    }
    catch (exception& e) {
        fprintf(f,"Failed starting eve.\n%s.\n",e.what());
        fclose(f);
        throw(e);
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {   
        pt = waitFor(img,login,pt);
        if (pt == NULL) return -1;
        sc.mouseMove(pt->x+100,pt->y+40);
        //keyboard input
        password();
        sc.mouseMove(pt->x+100,pt->y+60);
        sc.mouseClick(1);
    
        sleep(1);
        delete pt;
        pt = NULL;
        //Click login picture
        sleep(1);
        pt = waitFor(img,small,pt,20);
        if (pt != NULL) {
            sc.mouseMove(pt->x+30,pt->y+30);
            sc.mouseClick(1);
            delete pt;
            pt = NULL;
        }
        pt = waitFor(img,big,pt);
        if (pt == NULL) return -1;
        sc.mouseMove(pt->x+100,pt->y+60);
        sc.mouseClick(1);
    }
    catch (exception& e) {
        fprintf(f,"Failed logging in.\n%s.\n",e.what());
        fclose(f);
        throw(e);
    }
    fclose(f);
    f = fopen("log.txt","a");

    try {
        delete pt;
        cvReleaseImage(&login); 
        cvReleaseImage(&big);
        cvReleaseImage(&small);
    }
    catch (exception& e) {
        fprintf(f,"Failed releasing login memory.\n%s.\n",e.what());
        fclose(f);
        throw(e);
    }
    fclose(f);
    f = fopen("log.txt","a");
    return 0;
}


