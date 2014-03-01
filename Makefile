CC=gcc

CFLAGS= `pkg-config --cflags gtk+-2.0` -Wall -Werror -g
LIBS = `pkg-config --libs gtk+-2.0` 
BINARIES = 1_simplewindow 1_simplewindow_withicon 1_simplewindow_withwidgets 2_simplemenu 2_menus_imagemenus_etc 2_menus_check 2_menus_toolbar 2_menus_undoredo 3_gtkfixed 3_gtkvbox 3_gtktable 3_gtkalignment 3_windows 4_1_callbacks 4_2_movingwindow 4_3_entersignal 4_4_disconnectingcallback 4_5_dragdrop 4_6_timer 5_1_dialogs 5_2_aboutdialog 6_2_gtkcheckbutton

all: $(BINARIES)

clean:
	rm -f *.o *~ $(BINARIES) 


# basic - display window only
1_simplewindow: 1_simplewindow.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow.o $(LIBS)


# with icon
1_simplewindow_withicon: 1_simplewindow_withicon.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow_withicon.o $(LIBS)


# simple widgets
1_simplewindow_withwidgets: 1_simplewindow_withwidgets.o
	$(CC) -o $@ $(CFLAGS) 1_simplewindow_withwidgets.o $(LIBS)


# simple menu
2_simplemenu: 2_simplemenu.o
	$(CC) -o $@ $(CFLAGS) 2_simplemenu.o $(LIBS)


# simple menu with image menus, mnemonics and accelerators.
2_menus_imagemenus_etc: 2_menus_imagemenus_etc.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 2_menus_imagemenus_etc.o $(LIBS)


# simple menu with image menus, mnemonics and accelerators.
2_menus_check: 2_menus_check.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 2_menus_check.o $(LIBS)

# simple toolbar
2_menus_toolbar: 2_menus_toolbar.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 2_menus_toolbar.o $(LIBS)


# demonstrates activation/inactivation of toolbar items (undo/redo)
2_menus_undoredo: 2_menus_undoredo.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 2_menus_undoredo.o $(LIBS)

# fixed container widget
3_gtkfixed: 3_gtkfixed.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 3_gtkfixed.o $(LIBS)


# vbox container widget
3_gtkvbox: 3_gtkvbox.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 3_gtkvbox.o $(LIBS)

# table container widget
3_gtktable: 3_gtktable.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 3_gtktable.o $(LIBS)

# gtkalignment container, controls alignment and size of its child widget
3_gtkalignment: 3_gtkalignment.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 3_gtkalignment.o $(LIBS)

# dialog for managing all opened windows (or tabs) - from JDeveloper application
3_windows: 3_windows.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 3_windows.o $(LIBS)


# Event handling - intro to callback functions
4_1_callbacks: 4_1_callbacks.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 4_1_callbacks.o $(LIBS)

# Event handling - moving window
4_2_movingwindow: 4_2_movingwindow.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 4_2_movingwindow.o $(LIBS)

# Event handling - enter signal
4_3_entersignal: 4_3_entersignal.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 4_3_entersignal.o $(LIBS)

# Event handling - disconnecting callback functions
4_4_disconnectingcallback: 4_4_disconnectingcallback.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 4_4_disconnectingcallback.o $(LIBS)


# Event handling - drag and drop example
4_5_dragdrop: 4_5_dragdrop.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 4_5_dragdrop.o $(LIBS)

# Event handling - timer function
4_6_timer: 4_6_timer.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 4_6_timer.o $(LIBS)


# Dialogs
5_1_dialogs: 5_1_dialogs.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 5_1_dialogs.o $(LIBS)

# About Dialog
5_2_aboutdialog: 5_2_aboutdialog.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 5_2_aboutdialog.o $(LIBS)

# About Dialog
6_2_gtkcheckbutton: 6_2_gtkcheckbutton.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) 6_2_gtkcheckbutton.o $(LIBS)

