// Implements basic drawing functions for a cairo drawing area

#include <gtk/gtk.h>
#include "pdpgui_draw.h"

#define DEFAULT_UNIT_SIZE 20

void pdpgui_draw_unit (cairo_t *cr, 
		       PdpguiCoords unit_centre, 
		       PdpguiColourRgb colour_off,
		       PdpguiColourRgb colour_on,
		       double activation) {

  // activation should be real-valued proportion from 0 to 1
  // don't worry about negative activations or resting state for now

  cairo_set_source_rgb (cr, colour_off.r, colour_off.g, colour_off.b);
  cairo_arc (cr, unit_centre.x, unit_centre.y, DEFAULT_UNIT_SIZE, 0, 2*G_PI);
  cairo_fill(cr);

  cairo_set_source_rgb (cr, colour_on.r, colour_on.g, colour_on.b);
  cairo_arc (cr, unit_centre.x, unit_centre.y, DEFAULT_UNIT_SIZE*activation, 0, 2*G_PI);
  cairo_fill(cr);

}


void pdpgui_draw_connection (cairo_t *cr, 
			     PdpguiCoords unit_centre_lower, 
			     PdpguiCoords unit_centre_upper) {

  // default black connections
  cairo_set_source_rgb (cr, 0, 0, 0);

  // remember to invert y axis
  cairo_move_to (cr, unit_centre_lower.x, unit_centre_lower.y - DEFAULT_UNIT_SIZE);
  cairo_line_to (cr, unit_centre_upper.x, unit_centre_upper.y + DEFAULT_UNIT_SIZE);
  cairo_stroke(cr);

}



void pdpgui_draw_connection_curved (cairo_t *cr, 
				    PdpguiCoords unit_centre_lower, 
				    PdpguiCoords unit_centre_upper,
				    PdpguiCoords intermediate_lower,
				    PdpguiCoords intermediate_upper) {

  // default black connections
  cairo_set_source_rgb (cr, 0, 0, 0);

  // remember to invert y axis
  cairo_move_to (cr, unit_centre_lower.x, unit_centre_lower.y - DEFAULT_UNIT_SIZE);
  cairo_curve_to (cr,
		  intermediate_lower.x, intermediate_lower.y, 
		  intermediate_upper.x, intermediate_upper.y, 
		  unit_centre_upper.x, unit_centre_upper.y + DEFAULT_UNIT_SIZE);
  cairo_stroke(cr);

}
 
