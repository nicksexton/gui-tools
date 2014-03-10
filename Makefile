CC=gcc

CFLAGS= `pkg-config --cflags gtk+-3.0` -Wall -Werror -g
LIBS = `pkg-config --libs gtk+-3.0` -lm

OBJECTS = lib_cairox.o

BINARIES = gtk_notebook gtk_drawingarea gtk_pango_layout gtk_config_files pdpgui_architecture

all: $(BINARIES)

clean:
	rm -f *.o *~ $(BINARIES) 


# Creates a multi-tabbed notebook in the main window
gtk_notebook: gtk_notebook.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk_notebook.o $(LIBS)


# Creates a multi-tabbed notebook in the main window
gtk_drawingarea: gtk_drawingarea.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk_drawingarea.o $(LIBS)

gtk_pango_layout: gtk_pango_layout.o lib_cairox.o
	$(CC) -o $@ $(CFLAGS) lib_cairox.o $(LDFLAGS) gtk_pango_layout.o $(LIBS)

gtk_config_files: gtk_config_files.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk_config_files.o $(LIBS)




# example - draws a basic network architecture inside a multi-tabbed notebook
pdpgui_architecture: pdpgui_architecture.o pdpgui_draw.o lib_cairox.o
	$(CC) -o $@ $(CFLAGS) pdpgui_draw.o lib_cairox.o $(LDFLAGS) pdpgui_architecture.o $(LIBS)

pdpgui_draw.o: 
	$(CC) -c pdpgui_draw.c $(CFLAGS) $(LDFLAGS) $(LIBS)

lib_cairox.o:
	$(CC) -c lib_cairox.c $(CFLAGS) $(LDFLAGS) $(LIBS)

