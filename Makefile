CC=gcc

CFLAGS= `pkg-config --cflags gtk+-2.0` -Wall -Werror -g
LIBS = `pkg-config --libs gtk+-2.0` 


all: 1_simplewindow 1_simplewindow_withicon 1_simplewindow_withwidgets 2_simplemenu 2_menus_imagemenus_etc

# basic - display window only
1_simplewindow: 1_simplewindow.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow.o $(LIBS)

#1_simplewindow.o: 
#	$(CC) -c 1_simplewindow.c $(CFLAGS) $(LIBS)


# with icon
1_simplewindow_withicon: 1_simplewindow_withicon.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow_withicon.o $(LIBS)

#1_simplewindow_withicon.o: 
#	$(CC) -c 1_simplewindow_withicon.c $(CFLAGS) $(LIBS)

# simple widgets
1_simplewindow_withwidgets: 1_simplewindow_withwidgets.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow_withwidgets.o $(LIBS)

#1_simplewindow_withwidgets.o: 
#	$(CC) -c 1_simplewindow_withwidgets.c $(CFLAGS) $(LIBS)


# simple menu
2_simplemenu: 2_simplemenu.o
	$(CC) -o $@ $(CFLAGS) 2_simplemenu.o $(LIBS)

#2_simplemenu.o: 
#	$(CC) -c 2_simplemenu.c $(CFLAGS) $(LIBS)


# simple menu with image menus, mnemonics and accelerators.
2_menus_imagemenus_etc: 2_menus_imagemenus_etc.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 2_menus_imagemenus_etc.o $(LIBS)

# 2_menus_imagemenus_etc.o: 
#	$(CC) -c 2_menus_imagemenus_etc.c $(CFLAGS) $(LIBS)




clean:
	rm -f *.o *~ 1_simplewindow 1_simplewindow_withicon 1_simplewindow_withwidgets 2_simplemenu 2_menus_imagemenus_etc