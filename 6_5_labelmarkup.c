#include <gtk/gtk.h>


int main (int argc, char **argv) {
  
  GtkWidget *window;
  GtkWidget *label;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Markup Label");

  char *str = "<b>ZetCode</b>, Knowledge only matters";
  
  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), str);
  
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_container_add (GTK_CONTAINER(window), label);
  gtk_widget_show(label);

  gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);

  g_signal_connect_swapped (window, "destroy", 
			    G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
