#include <gtk/gtk.h>

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

// inits a gtk drawing area to paint arbitrary things to via cairo

static void draw_something (GtkWidget *widget, cairo_t *cr, gpointer data) {

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
  g_signal_connect (drawing_area, "draw", G_CALLBACK(draw_something), NULL);
  

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  gtk_grid_attach (GTK_GRID(grid), drawing_area, 0, 0, 1, 1);

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
