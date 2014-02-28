CC=gcc
CFLAGS= `pkg-config --libs --cflags gtk+-2.0` -Wall -Werror -g

all: 1_simplewindow 1_simplewindow_withicon 1_simplewindow_withwidgets

# basic - display window only
1_simplewindow: 1_simplewindow.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow.o

1_simplewindow.o: 
	$(CC) -c 1_simplewindow.c $(CFLAGS) 


# with icon
1_simplewindow_withicon: 1_simplewindow_withicon.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow_withicon.o

1_simplewindow_withicon.o: 
	$(CC) -c 1_simplewindow_withicon.c $(CFLAGS) 

# simple widgets
1_simplewindow_withwidgets: 1_simplewindow_withwidgets.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow_withwidgets.o

1_simplewindow_withwidgets.o: 
	$(CC) -c 1_simplewindow_withwidgets.c $(CFLAGS) 




clean:
	rm -f *.o *~ 1_simplewindow 1_simplewindow_withicon 1_simplewindow_withwidgets