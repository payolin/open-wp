#include <stdio.h>
#include <X11/Xlib.h>
#include <err.h>

static Display* disp;
static int scr;
static Window root;

#define POSX 500
#define POSY 500
#define BORDER 0

int main(){

    Window win;
    XEvent event;

    disp = XOpenDisplay(NULL);

    if(disp == NULL){
	errx(1, "can't open the display");
    }
    scr = DefaultScreen(disp);
    root = RootWindow(disp,scr);

    XWindowAttributes getWinAttr;
    XGetWindowAttributes(disp, root, &getWinAttr);

    XSetWindowAttributes wa;
    wa.override_redirect = True;

    win = XCreateWindow(disp,root,POSX,POSY,getWinAttr.width,getWinAttr.height,BORDER, BlackPixel(disp,scr), CopyFromParent,
                              CopyFromParent, 0, &wa);

    XSetWindowBackground(disp, win, WhitePixel(disp,scr));

    XMapWindow(disp,win);

    while (XNextEvent(disp, &event) == 0){

    }

    XUnmapWindow(disp,win);
    XDestroyWindow(disp,win);
    XCloseDisplay(disp);

    return 0;
}