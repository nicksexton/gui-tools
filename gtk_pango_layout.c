#include <gtk/gtk.h>
#include "lib_cairox.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600



// inits a gtk drawing area to paint arbitrary things to via cairo

static void pango_layout (GtkWidget *widget, cairo_t *cr, gpointer data) {

  PangoLayout *layout;
  CairoxTextParameters text_params;
  char textbuf[160];
  
  layout = pango_cairo_create_layout (cr);

  // set colour for background
  cairo_set_source_rgb (cr, 1, 1, 1);
  // fill background colour
  cairo_paint (cr);

  g_snprintf (textbuf, 160, "Labyrinth");

  // print large
  pangox_layout_set_font_size (layout, 15);

  cairox_text_parameters_set (&text_params, 50, 50, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_TOP, 0.0);
  cairox_text_parameters_set_foreground (&text_params, 1, 0, 0);
  cairox_paint_pango_text (cr, &text_params, layout, textbuf);


  // print small
  pangox_layout_set_font_size (layout, 10);

  cairox_text_parameters_set (&text_params, 50, 100, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_TOP, 0.0);
  cairox_text_parameters_set_foreground (&text_params, 1, 0, 0);
  cairox_paint_pango_text (cr, &text_params, layout, textbuf);


  // print many
  
  int i;

  for (i = 0; i < 10; i ++) {
    cairox_text_parameters_set (&text_params, 
				50 + (i * 50), 
				(150 + i * 50), 
				PANGOX_XALIGN_LEFT, PANGOX_YALIGN_TOP, 0.0);
  cairox_text_parameters_set_foreground (&text_params, 1, 0, 0);
  cairox_paint_pango_text (cr, &text_params, layout, textbuf);
  }




}


int main (int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *drawing_area;

  gtk_init (&argc, &argv);

  /* create a new window, and set its title */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "gtk drawing area");
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  // gtk_container_set_border_width (GTK_CONTAINER(window), 10);

  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);


  // Create a new drawing area;
  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT);
  g_signal_connect (drawing_area, "draw", G_CALLBACK(pango_layout), NULL);
  

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  gtk_grid_attach (GTK_GRID(grid), drawing_area, 0, 0, 1, 1);

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
