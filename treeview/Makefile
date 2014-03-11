CC=gcc

CFLAGS= `pkg-config --cflags gtk+-3.0` -Wall -Werror -g
LIBS = `pkg-config --libs gtk+-3.0` -lm

OBJECTS = lib_cairox.o

BINARIES = gtk_treeview

all: $(BINARIES)

clean:
	rm -f *.o *~ $(BINARIES) 


# Creates a multi-tabbed notebook in the main window
gtk_treeview: gtk_treeview.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk_treeview.o $(LIBS)

