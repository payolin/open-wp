#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <err.h>
#include <malloc.h>

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

    GC gc = XCreateGC(disp, win, CopyFromParent, CopyFromParent);

    // Load the image
    XImage *image = XCreateImage(disp, CopyFromParent, DefaultDepth(disp, scr),
                                 ZPixmap, 0, NULL, getWinAttr.width,getWinAttr.height, 32, 0);
    if (image == NULL) {
        fprintf(stderr, "Error: Failed to create XImage.\n");
        XCloseDisplay(disp);
        return 1;
    }

    FILE *file = fopen("image_to_display.bmp", "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Failed to open image file.\n");
        XDestroyImage(image);
        XCloseDisplay(disp);
        return 1;
    }

    size_t image_size = getWinAttr.width * getWinAttr.height * 4;  // Assuming 32-bit image
    unsigned char *image_data = (unsigned char *)malloc(image_size);
    if (image_data == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for image data.\n");
        fclose(file);
        XDestroyImage(image);
        XCloseDisplay(disp);
        return 1;
    }

    fread(image_data, sizeof(unsigned char), image_size, file);
    fclose(file);
    image->data = (char *)image_data;

    //Draws the image name as background
    XPutImage(disp, win, gc, image, 0, 0, 0, 0, getWinAttr.width,getWinAttr.height);

    // Show the image
    XFlush(disp);

    XMapWindow(disp,win);

    while (XNextEvent(disp, &event) == 0){

    }

    XUnmapWindow(disp,win);
    XDestroyWindow(disp,win);
    XCloseDisplay(disp);

    return 0;
}