#include <gtk/gtk.h>

// Signal handler for the "clicked" signal of the button
// Each click generates a progress bar pulse

static void on_button_click(GtkButton *button, gpointer user_data) {
  GtkProgressBar *progress_bar = user_data;
  gtk_progress_bar_pulse (progress_bar);

}

static void activate(GtkApplication *app, gpointer user_data) {

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *progress_bar;

  // Create a window with a title, default size, and set border width
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW(window), "Grid example");

  // gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);
  // gtk_container_set_border_width (GTK_CONTAINER(window), 10);

  // create a button with a label
  button = gtk_button_new_with_label ("Button");

  // create the progress bar
  progress_bar = gtk_progress_bar_new ();

  // create a grid and attach the button and progress bar
  grid = gtk_grid_new ();
  gtk_grid_attach (GTK_GRID (grid), button, 1, 1, 1, 1);
  gtk_grid_attach_next_to (GTK_GRID (grid),
			   progress_bar,
			   button,
			   GTK_POS_BOTTOM, 1, 1);


  // connect the clicked signal to the callback
  g_signal_connect(GTK_BUTTON(button), "clicked", 
		   G_CALLBACK(on_button_click), progress_bar);

  gtk_container_add (GTK_CONTAINER(window), GTK_WIDGET(grid));

  gtk_widget_show_all (window);
}

int main (int argc, char *argv[]) {

  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run (G_APPLICATION(app), argc, argv);
  g_object_unref (app);

  return status;
}

