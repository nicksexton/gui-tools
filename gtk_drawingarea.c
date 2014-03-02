#include <gtk/gtk.h>

// inits a gtk drawing area to paint arbitrary things to via cairo

int main (int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *drawing_area;

  gtk_init (&argc, &argv);

  /* create a new window, and set its title */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "gtk drawing area");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  // gtk_container_set_border_width (GTK_CONTAINER(window), 10);

  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  // Create a new drawing area;
  drawing_area = gtk_drawing_area_new();
  gtk_grid_attach (GTK_GRID(grid), drawing_area, 0, 0, 1, 1);

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);


  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
