CC=gcc

CFLAGS= `pkg-config --cflags gtk+-3.0` -Wall -Werror -g
LIBS = `pkg-config --libs gtk+-3.0` 

BINARIES = gtk_notebook gtk_drawingarea

all: $(BINARIES)

clean:
	rm -f *.o *~ $(BINARIES) 


# Creates a multi-tabbed notebook in the main window
gtk_notebook: gtk_notebook.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk_notebook.o $(LIBS)


# Creates a multi-tabbed notebook in the main window
gtk_drawingarea: gtk_drawingarea.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk_drawingarea.o $(LIBS)

