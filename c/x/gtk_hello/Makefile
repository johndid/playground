GTK_INCLUDE = -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0/
GTK_LIB = -L/usr/local/lib
X11_LIB = -L/usr/X11R6/lib
CC = gcc -g -Wall
CFLAGS = $(GTK_INCLUDE)
LDFLAGS = $(GTK_LIB) $(X11_LIB) -lgtk -lgdk -lglib -lX11 -lXext -lm

OBJS = hello.o

hello:	$(OBJS)
#	$(CC) $(GTK_LIB) $(X11_LIB) $(OBJS) -o hello $(LDFLAGS)

clean:
	rm -f *.o *~ hello