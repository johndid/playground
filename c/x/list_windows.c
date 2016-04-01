#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<stdio.h>

int main()
{
    Display *display;
    Window rootwin;
    XEvent event;

    display = XOpenDisplay( NULL );
    rootwin = DefaultRootWindow( display );
    XSelectInput( display, rootwin, SubstructureNotifyMask );

    printf("XServer vendor\t: %s\n",XServerVendor(display));
    printf("XServer release\t: %d\n",XVendorRelease(display));
    printf("Screen count\t: %d\n",XScreenCount(display));
    printf("Protocol ver\t: %d\n",XProtocolVersion(display));
    printf("Protocol rev\t: %d\n",XProtocolRevision(display));

    /* while ( 1 ) { */
    /*     XNextEvent( display, &event ); */
    /*     if ( event.type == MapNotify ) { */
    /*         XMapEvent *mapevent = (XMapEvent *)&event; */
    /*         printf( "Mapped    : 0x%x\n", (unsigned int)(mapevent->window) ); */
    /*     } */
    /*     if ( event.type == DestroyNotify ) { */
    /*         XDestroyWindowEvent *destroywindowevent = (XDestroyWindowEvent *)&event; */
    /*         printf( "Destroyed : 0x%x\n", (unsigned int)(destroywindowevent->window) ); */
    /*     } */
    /*     if ( event.type == ReparentNotify ) { */
    /*         XReparentEvent *reparentevent = (XReparentEvent *)&event; */
    /*         printf( "Reparented: 0x%x to 0x%x\n", (unsigned int)(reparentevent->window), (unsigned int)(reparentevent->parent) ); */
    /*     } */
    /* } */

    return 0;
}
