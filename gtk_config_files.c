
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#define CONFIG_FILE gtk_config_file.conf
#define FILENAME_MAX_LENGTH 40

// callback function to read file contents
gboolean button_clicked_process_config_file (GtkWidget *widget, gpointer data) {

  char filename[20] = {"CONFIG_FILE"};
  FILE *config_file;
  // char c;

  config_file = fopen(filename, "r");
  if (config_file == NULL) {
    printf ("error! gtk_config_file.conf does not exist\n");
    return FALSE;
  }

  
  return TRUE;
}

void select_file (GtkComboBoxText *widget, gpointer data) {

  GtkComboBoxText *combo_box = widget;
  // char *tmp[FILENAME_MAX_LENGTH];

  gchar *filename = gtk_combo_box_text_get_active_text (combo_box);


    // just print filename for now
  g_print ("file %s selected", filename);
  gtk_label_set_text(GTK_LABEL(data), filename);

  g_free (filename);

}



static GtkWidget* create_notepage_copper() {

  GtkWidget *grid;
  GtkWidget *label1, *label2;
  GtkWidget *file_select;

  char filename[FILENAME_MAX_LENGTH];
  strcpy (filename, "no file selected");

  label1 = gtk_label_new("Select config file");
  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);

  label2 = gtk_label_new(filename);

  file_select = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(file_select), 
				 "gtk_config_file.conf");


  g_signal_connect (file_select, "changed", G_CALLBACK(select_file), (gpointer)label2);




  grid = gtk_grid_new();
  gtk_grid_attach (GTK_GRID(grid), label1, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), file_select, 0, 1, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), label2, 0, 2, 1, 1);

  gtk_widget_set_vexpand (GTK_WIDGET(grid), TRUE);

  gtk_widget_show_all(grid);
  return (grid);

}
  
static void activate(GtkApplication *app, gpointer user_data) {

  GtkWidget *window;
  GtkWidget *grid;

  GtkWidget *toolbar;
  GtkToolItem *tool_item;

  GtkWidget *notes;


  int position = 0; // toolbar position

  // Create a window with a title, default size, and set border width
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW(window), "GUI: notebook");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER(window), 10);
  

  // ------------- TOOLBAR ----------------
  // Create a basic toolbar
  toolbar = gtk_toolbar_new();
  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  tool_item = gtk_tool_button_new_from_stock (GTK_STOCK_REFRESH);
  g_signal_connect (G_OBJECT(tool_item), 
		    "clicked", 
		    G_CALLBACK(button_clicked_process_config_file), 
		    NULL);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, position ++);

  tool_item = gtk_separator_tool_item_new();
  gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(tool_item), FALSE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, position ++);

  tool_item = gtk_tool_button_new_from_stock (GTK_STOCK_CLOSE);
  // connect application quit callback here
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, position ++);


  // ------------- NOTEPAD -----------------

  notes = gtk_notebook_new();

  gtk_notebook_append_page(GTK_NOTEBOOK(notes), 
			   create_notepage_copper(), 
			   gtk_label_new("Data"));


  // Create a full-window grid to contain toolbar and the notebook
  grid = gtk_grid_new();
  gtk_grid_attach (GTK_GRID(grid), toolbar, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), notes, 0, 1, 1, 1);

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

