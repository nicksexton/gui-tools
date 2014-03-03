#ifndef pdpgui_draw_h
#define pdpgui_draw_h

#include <gtk/gtk.h>

typedef struct pdpgui_coords {
  double x; 
  double y; 
} PdpguiCoords;

typedef struct pdpgui_colour_rgb {
  double r; 
  double g; 
  double b;
} PdpguiColourRgb;


void pdpgui_draw_unit (cairo_t *cr, 
		       PdpguiCoords unit_centre, 
		       PdpguiColourRgb colour_off,
		       PdpguiColourRgb colour_on,
		       double activation);


void pdpgui_draw_connection (cairo_t *cr, 
			     PdpguiCoords unit_centre_lower, 
			     PdpguiCoords unit_centre_upper);

void pdpgui_draw_connection_curved (cairo_t *cr, 
				    PdpguiCoords unit_centre_lower, 
				    PdpguiCoords unit_centre_upper,
				    PdpguiCoords intermediate_lower,
				    PdpguiCoords intermediate_upper);

#endif
