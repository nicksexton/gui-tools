// Implements basic drawing functions for a cairo drawing area

#include <gtk/gtk.h>
#include <stdlib.h>
#include "lib_cairox.h"
#include "pdpgui_draw.h"


#define DEFAULT_UNIT_SIZE 20

#define AXIS_MARGIN_X 0.1
#define AXIS_MARGIN_Y 0.1
#define AXIS_WIDTH 4
#define AXIS_LABEL_FONT_SIZE 9

#define FONT_HEIGHT 12 // fix with access function



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
 
void pdpgui_draw_graph_axes (cairo_t *cr, 
			     guint window_width, guint window_height,
			     int x_divisions, int y_divisions,
			     double x_min, double x_max, 
			     double y_min, double y_max){

  double axis_division_x; 
  // double axis_division_y;
  int i;

  double axis_margin_x = AXIS_MARGIN_X * window_width;
  double axis_margin_y = AXIS_MARGIN_Y * window_height;
  double text_height; 

  PangoLayout *layout;
  char textbuf[32];
  CairoxTextParameters text_params;


  axis_division_x = (window_width - (2 * axis_margin_x)) / x_divisions;

  printf ("axis margins:\t x: %4.2f\t y: %4.2f\n", axis_margin_x, axis_margin_y);


  // set line parameters
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_set_line_width (cr, 2);


  // draw x axis
  
  cairo_move_to (cr, axis_margin_x, (window_height - axis_margin_y));
  cairo_line_to (cr, (window_width - axis_margin_x), (window_height - axis_margin_y));
  cairo_stroke(cr);

  // x axis tick marks:
  for (i = 0; i < (x_divisions + 1); i ++) {
    cairo_move_to (cr, axis_margin_x + (i * axis_division_x), 
		   (window_height - axis_margin_y));
    cairo_line_to (cr, axis_margin_x + (i * axis_division_x), 
		   (window_height - axis_margin_y + (0.01 * window_height)));
    cairo_stroke(cr);


  }
  

  // axis labels
  // set text parameters
  

  layout = pango_cairo_create_layout (cr);
  pangox_layout_set_font_size (layout, 10);
      
  for (i = 0; i < (x_divisions + 1); i ++) {


    g_snprintf (textbuf, 10, "%3.1f", (x_min + (i * (x_max - x_min) / x_divisions)));
 
    // offset y for text height

    text_height = pangox_layout_get_font_height (layout);
    
    cairox_text_parameters_set (&text_params, 
				axis_margin_x + (i * axis_division_x), 
				(window_height - axis_margin_y) + (0.015 * window_height),
				PANGOX_XALIGN_CENTER, PANGOX_YALIGN_TOP, 0.0);
    
    printf ("label at: %4.2f, %4.2f\n", 
	    (axis_margin_x + (i * axis_division_x)), 
	    (window_height - axis_margin_y + (0.01 * window_height) + text_height)
	    );
    
    cairox_paint_pango_text (cr, &text_params, layout, textbuf);
  }


  /*
  // draw y axis
  cairo_move_to (cr, axis_margin_x, axis_margin_y);
  cairo_line_to (cr, axis_margin_x, (1 - axis_margin_y));
  cairo_stroke(cr);

  // y axis tick marks:
  for (i = 0; i < (y_divisions +1); i ++) {
    axis_division_y = (1 - (2 * axis_margin_y)) / y_divisions;
    cairo_move_to (cr, axis_margin_x, 
  		   (1 - axis_margin_y) - (i * axis_division_y));
    cairo_line_to (cr, axis_margin_x - 0.02, 
  		   (1 - axis_margin_y) - (i * axis_division_y));
    cairo_stroke(cr);
  }

  */


  // y axis scale

  // g_object_unref (layout);
  // cairo_destroy(cr);

}
