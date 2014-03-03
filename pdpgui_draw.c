// Implements basic drawing functions for a cairo drawing area

#include <gtk/gtk.h>

// example drawing callback function
void pdpgui_draw_example (GtkWidget *widget, cairo_t *cr, gpointer data) {

  // set colour for background
  cairo_set_source_rgb (cr, 1, 1, 1);
  // fill background colour
  cairo_paint (cr);

  // set colour for rectangle
  cairo_set_source_rgb (cr, 0.42, 0.65, 0.80);
  // set line width
  cairo_set_line_width(cr, 6);
  // draw rectangle path beginning at 3, 3
  cairo_rectangle (cr, 3, 3, 100, 100);
  // stroke
  cairo_stroke (cr);

  // draw circle
  cairo_set_source_rgb(cr, 0.17, 0.63, 0.12);
  cairo_set_line_width(cr, 2);
  cairo_arc(cr, 150, 210, 20, 0, 2*G_PI);
  cairo_stroke(cr);

  // draw horizontal line
  cairo_set_source_rgb(cr, 0.77, 0.16, 0.13);
  cairo_set_line_width(cr, 6);
  cairo_move_to(cr, 80, 160);
  cairo_line_to(cr, 200, 160);
  cairo_stroke(cr);

}
