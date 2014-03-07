CC=gcc

CFLAGS= `pkg-config --cflags gtk+-3.0` -Wall -Werror -g
LIBS = `pkg-config --libs gtk+-3.0` 


BINARIES = string_parse

all: $(BINARIES)

clean:
	rm -f *.o *~ $(BINARIES) 


# Creates a multi-tabbed notebook in the main window
string_parse: string_parse.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) string_parse.o $(LIBS)

