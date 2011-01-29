#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#ifndef XINPUT
#define XINPUT

class XInput {
    Display *d;
    public:
    XInput(){d = XOpenDisplay(NULL);}
    ~XInput(){};
    void mouseMove(int x,int y);
    void mouseClick(int button);
    void keyPress(int key,int state);
    void mouseDrag(int x, int y, int x1, int y1, int button); 
};

    void XInput::mouseDrag(int x, int y, int x1, int y1, int button) {
        mouseMove(x,y);
        XEvent event;
        if(d == NULL)
        {
          fprintf(stderr, "Error Display !!!\n");
          exit(EXIT_FAILURE);
        }
        memset(&event, 0x00, sizeof(event));
        event.type = ButtonPress; 
        event.xbutton.button = button;
        event.xbutton.same_screen = True;
        XQueryPointer(d, RootWindow(d, DefaultScreen(d)),
          &event.xbutton.root,
          &event.xbutton.window,
          &event.xbutton.x_root,
          &event.xbutton.y_root,
          &event.xbutton.x,
          &event.xbutton.y,
          &event.xbutton.state);
        event.xbutton.subwindow = event.xbutton.window;
        while(event.xbutton.subwindow)
        {
          event.xbutton.window = event.xbutton.subwindow;
          XQueryPointer(d, event.xbutton.window,
            &event.xbutton.root,
            &event.xbutton.subwindow,
            &event.xbutton.x_root,
            &event.xbutton.y_root,
            &event.xbutton.x,
            &event.xbutton.y,
            &event.xbutton.state);
        }
        if(XSendEvent(d, PointerWindow, True, 0xffff, &event) == 0) fprintf(stderr, "Error event !!!\n");
        XFlush(d);
        event.type = MotionNotify;
        if(XSendEvent(d, PointerWindow, True, 0xffff, &event) == 0) fprintf(stderr, "Error event !!!\n");
        XFlush(d);
        usleep(1000);
        if(XSendEvent(d, PointerWindow, True, 0xffff, &event) == 0) fprintf(stderr, "Error event !!!\n");
        usleep(100000);
        mouseMove(x1,y1);
        memset(&event, 0x00, sizeof(event));
        event.xbutton.button = button;
        event.xbutton.same_screen = True;
        XQueryPointer(d, RootWindow(d, DefaultScreen(d)),
          &event.xbutton.root,
          &event.xbutton.window,
          &event.xbutton.x_root,
          &event.xbutton.y_root,
          &event.xbutton.x,
          &event.xbutton.y,
          &event.xbutton.state);
        event.type = ButtonRelease;
        event.xbutton.state = 0x100;
        if(XSendEvent(d, PointerWindow, True, 0xffff, &event) == 0) fprintf(stderr, "Error event !!!\n");
        XFlush(d);
        mouseClick(button);
        usleep(500000);
    }

void XInput::mouseMove(int x, int y) {
        XEvent event;
        XQueryPointer(d, RootWindow(d, DefaultScreen(d)),
          &event.xbutton.root,
          &event.xbutton.window,
          &event.xbutton.x_root,
          &event.xbutton.y_root,
          &event.xbutton.x,
          &event.xbutton.y,
          &event.xbutton.state);
        if(d == NULL)
        {
            fprintf(stderr,"Error");
            exit(EXIT_FAILURE);
        }
        XWarpPointer(d, None, None, event.xbutton.x,event.xbutton.y,0,0, x-event.xbutton.x, y-event.xbutton.y);
    }
    
    void XInput::keyPress(int c,int state=0) {
        if (state !=0) {
            XTestFakeKeyEvent(d,XKeysymToKeycode(d,state),True,0);
            XFlush(d);
        }
    
        XTestFakeKeyEvent(d,XKeysymToKeycode(d,c),True,0);
        XFlush(d);
        usleep(1000);
        XTestFakeKeyEvent(d,XKeysymToKeycode(d,c),False,0);
        XFlush(d);
        usleep(1000);
        if (state !=0) {
            XTestFakeKeyEvent(d,XKeysymToKeycode(d,state),False,0);
            XFlush(d);
        }
    }
    
    void XInput::mouseClick(int button)
    {
          XEvent event;
    
          if(d == NULL)
          {
            fprintf(stderr, "Error Display !!!\n");
            exit(EXIT_FAILURE);
          }
          memset(&event, 0x00, sizeof(event));
          event.type = ButtonPress; 
          event.xbutton.button = button;
          event.xbutton.same_screen = True;
          XQueryPointer(d, RootWindow(d, DefaultScreen(d)),
            &event.xbutton.root,
            &event.xbutton.window,
            &event.xbutton.x_root,
            &event.xbutton.y_root,
            &event.xbutton.x,
            &event.xbutton.y,
            &event.xbutton.state);
          event.xbutton.subwindow = event.xbutton.window;
          while(event.xbutton.subwindow)
          {
            event.xbutton.window = event.xbutton.subwindow;
            XQueryPointer(d, event.xbutton.window,
              &event.xbutton.root,
              &event.xbutton.subwindow,
              &event.xbutton.x_root,
              &event.xbutton.y_root,
              &event.xbutton.x,
              &event.xbutton.y,
              &event.xbutton.state);
          }
          if(XSendEvent(d, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error event !!!\n");
          XFlush(d);
          usleep(100);
          event.type = ButtonRelease;
          event.xbutton.state = 0x100;
          if(XSendEvent(d, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error event !!!\n");
          XFlush(d);
    }
#endif
