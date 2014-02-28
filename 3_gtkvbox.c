#include <gtk/gtk.h>

int main (int argc, char *argv[]) {
  
  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *settings;
  GtkWidget *accounts;
  GtkWidget *loans;
  GtkWidget *cash;
  GtkWidget *debts;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 230, 250);
  gtk_window_set_title(GTK_WINDOW(window), "GtkVbox");
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);
  
  // GtkVBox in action
  vbox = gtk_vbox_new (TRUE, 1); // homogeneous parameter set to TRUE, spacing is 1 pixel
  gtk_container_add(GTK_CONTAINER(window), vbox);
  
  settings = gtk_button_new_with_label("Setttings");
  accounts = gtk_button_new_with_label("Accounts");
  loans = gtk_button_new_with_label("Loans");
  cash = gtk_button_new_with_label("Cash");
  debts = gtk_button_new_with_label("Debts");

  // adding items to a vbox (sized uniformly to fit window)
  gtk_box_pack_start(GTK_BOX(vbox), settings, TRUE, TRUE, 0); 
  // params: container widget, child widget, expand, fill, padding
  gtk_box_pack_start(GTK_BOX(vbox), accounts, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), loans, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), cash, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), debts, TRUE, TRUE, 0);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
			   G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
