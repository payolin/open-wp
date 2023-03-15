#include <stdio.h>
#include <X11/Xlib.h>
#include <err.h>

static Display* disp;
static int scr;
static Window root;

#define POSX 500
#define POSY 500
#define WIDTH 500
#define HEIGHT 500
#define BORDER 15

int main(){

    Window win;
    XEvent event;

    if((disp = XOpenDisplay(NULL)) == NULL){
	errx(1, "can't open the display");
    }
    scr = DefaultScreen(disp);
    root = RootWindow(disp,scr);

    win = XCreateSimpleWindow(disp,root,POSX,POSY,WIDTH,HEIGHT,BORDER, BlackPixel(disp,scr), WhitePixel(disp,scr));
    XMapWindow(disp,win);

    while (XNextEvent(disp, &event) == 0){

    }

    XUnmapWindow(disp,win);
    XDestroyWindow(disp,win);
    XCloseDisplay(disp);

    return 0;
}
