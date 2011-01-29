#!/usr/bin/env python2
import cv, math, time, sys

windowName = 'Window'
cnt = 0
rect = [0,0,0,0]


def on_mouse(event,x,y,flags,param):
	if event == cv.CV_EVENT_LBUTTONDOWN:
		global cnt
		global rect
		rect[2*cnt] = x
		rect[2*cnt+1] = y
		cv.Circle(param,(x,y),3,cv.RGB(255,0,0),3)
		cnt = cnt + 1
		if cnt == 2:
			cnt = -1

def calibrate(image):
    global cnt
    cv.ShowImage(windowName,image)
    cv.SetMouseCallback(windowName,on_mouse,image)
    while(cnt>=0):
	    cv.ShowImage(windowName,image)
	    cv.WaitKey(100)
    cnt = 0


if len(sys.argv) < 3:
	print 'usage -- ./crop.py (filenames) outputname // crops 1080p'
	exit()
print sys.argv
len = len(sys.argv) 
outputname = sys.argv[len-1]
rect = [0,0,1920,1080]
for x in range(0,len-2):
    imloaded = cv.LoadImage(sys.argv[len-x-2])
    im = cv.LoadImage(sys.argv[len-x-2])
    #calibrate(im)
    im = cv.CreateImage((rect[2]-rect[0],rect[3]-rect[1]),cv.IPL_DEPTH_8U,3)
    src_region = cv.GetSubRect(imloaded, (rect[0],rect[1],rect[2]-rect[0],rect[3]-rect[1]))
    cv.Copy(src_region, im)
    cv.SaveImage('{:}{:02d}.png'.format(outputname,x),im)
print 'finished'
