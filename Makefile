CC=gcc

CFLAGS= `pkg-config --cflags gtk+-3.0` -Wall -Werror -g
LIBS = `pkg-config --libs gtk+-3.0` 

BINARIES = gtk3_entry gtk3_applicationwindow gtk3_containers_grid gtk3_packing gtk3_gtkbuilder

all: $(BINARIES)

clean:
	rm -f *.o *~ $(BINARIES) 


# GTK+3.0 examples: text entry
gtk3_entry: gtk3_entry.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk3_entry.o $(LIBS)



# GTK+3.0 examples: application window
gtk3_applicationwindow: gtk3_applicationwindow.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk3_applicationwindow.o $(LIBS)



# GTK+3.0 examples: containers: grid
gtk3_containers_grid: gtk3_containers_grid.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk3_containers_grid.o $(LIBS)


# GTK+3.0 examples: containers: grid
gtk3_packing: gtk3_packing.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk3_packing.o $(LIBS)

# GTK+3.0 examples: UI builder (gtkbuilder)
gtk3_gtkbuilder: gtk3_gtkbuilder.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) gtk3_gtkbuilder.o $(LIBS)
