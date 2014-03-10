gui-tools
=========

Repository for learning gtk and cairo

gtk2/ - code from the gtk2 tutorials at
www.zetcode.com/tutorials/gtktutorial/

gtk3/ - code from gtk3 tutorials


gtk_notebook.c: a simple two-page notebook
gtk_drawingarea.c: example code for creating a drawing area and drawing on it with cairo
gtk_pango_layout.c: eample code for using pango to put text on a cairo drawing area. 
		    NB uses Rick's cairo utility libraries (lib_cairox, lib_string)




pdpgui_draw.c - library which implements basic cairo drawing functions for
pdp objects (eg drawing units, drawing connections, etc)

string_parse.c - library of functions for reading config files and getting their data out
into a set of C data structures. Some functions should be customised for program-specific
data.

gtk_confic_files - example code for a gui which uses string_parse library to read parameter 
settings from a config file and updates a parameters page displaying current parameter 
settings. 

pdpgui_architecture.c - example code for a basic (mocked up) gui, 
tabbed notebook and architecture view tab.



