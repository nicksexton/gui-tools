gui-tools
=========

####conf_treestore####
A branch for exploring using gtk treestore as data structure to buffer extracted fields from config file
will require re-writing of string_parse.c
The tree store should be an application-independent buffer which enables viewing of segmented data

an application-specific translater function can then operate over the treestore to set parameters
(ie., a model_parameters struct which is defined in header file for _model file/module.


<pre>
      			 	      	 	    
   +---------------+	       o---------------+        +----------------+
   | config file:  |	       | treestore     +-->-----+ pdpgui viewer  |
   | params.conf  -+---------->+ data structure+---<----+  treeview      |
   |  		   | segment   |               +-->-+   +----------------+
   +---------------+ & parse   +---------------+    |   +----------------+
                 app-independent                    +->-+  model params  |
                                           translator   |  struct        |
                                          app-specific  +----------------+

</pre>



gtk_config_files - example code for a gui which uses string_parse library to read parameter
settings from a config file and updates a parameters page displaying current parameter
settings. NOTE that important program-specific settings (eg., parameter names) are hard coded
in string_parse.c


string_parse.c - generic library of functions for reading config files and getting their data out
into a set of C data structures. Uses GTK tree store as a data structure for fields extracted from
config files. Store data as pairs of strings (parameter name, parameter value). 
Application-specific translator functions should extract data from the tree store and convert from
strings into the relevant data type for each parameter.




####gui-tools master####

gtk2/ - code from the gtk2 tutorials at
www.zetcode.com/tutorials/gtktutorial/

gtk3/ - code from gtk3 tutorials


gtk_notebook.c: a simple two-page notebook
gtk_drawingarea.c: example code for creating a drawing area and drawing on it with cairo
gtk_pango_layout.c: eample code for using pango to put text on a cairo drawing area.
		    NB uses Rick's cairo utility libraries (lib_cairox, lib_string)



pdpgui_draw.c - library which implements basic cairo drawing functions for
pdp objects (eg drawing units, drawing connections, etc)



pdpgui_architecture.c - example code for a basic (mocked up) gui,
tabbed notebook and architecture view tab.

