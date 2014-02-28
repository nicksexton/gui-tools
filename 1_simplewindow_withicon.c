/* Tutorial from www.zetcode.com/tutorials/gtktutorial/firstprograms/ */


#include <gtk/gtk.h>

// pixel buffer for the window icon
GdkPixbuf *create_pixbuf(const gchar * filename) {
  GdkPixbuf *pixbuf;
  GError *error = NULL;
  pixbuf = gdk_pixbuf_new_from_file(filename, &error);
  if (!pixbuf) {
    fprintf(stderr, "%s\n", error->message);
    g_error_free(error);
  }

  return pixbuf;
}




int main (int argc, char *argv[]) {

  GtkWidget *window;

  // init the gtk library:
  gtk_init(&argc, &argv);

  // create a GtkWindow widget
  // NB toplevel windows have titlebar and border, and are managed by window manager
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Center");
  gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  // now set the icon
  gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("robot-icon.png"));

  // show the widget
  gtk_widget_show(window);


  // set window to react to destroy (close window)
  g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  
  // enter the gtk main loop (program sits and waits for events)
  gtk_main();

  return 0;
}

