
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include "string_parse.h"

#define CONFIG_FILE gtk_config_file.conf
#define FILENAME_MAX_LENGTH 40


typedef struct file_data {
  GtkWidget * filename_label; // store filename in the text of a gtk widget
  char filename[FILENAME_MAX_LENGTH];

  FILE * fp; // file pointer itself
  GenericParameterSet * data; // from string_parse.h
} FileData;


// callback function to read file contents
gboolean load_from_file (GtkWidget *widget, FileData *file_info) {

  file_info->fp = fopen(file_info->filename, "r");
  if (file_info->fp == NULL) {
    printf ("error! gtk_config_file.conf does not exist\n");
    return FALSE;
  }
  else {
    printf ("success! config file opened.\n");

    fclose(file_info->fp);
    printf ("success! config file closed.\n");
  }

  return TRUE;
}


void select_file (GtkComboBoxText *widget, FileData * config_file) {

  GtkComboBoxText *combo_box = widget;
  // char *tmp[FILENAME_MAX_LENGTH];

  gchar *filename = gtk_combo_box_text_get_active_text (combo_box);

    // just print filename for now

  g_print ("file %s selected", filename);
  strcpy (config_file->filename, filename);
  gtk_label_set_text(GTK_LABEL(config_file->filename_label), filename);

  g_free (filename);

}


static GtkWidget* display_generic_parameter_data (FileData *config_file) {
  // 
  GtkWidget *grid;
  GtkWidget *param1_name;
  GtkWidget *param1_1;
  GtkWidget *param1_2;

  GtkWidget *param2_name;
  GtkWidget *param2_1;
  GtkWidget *param2_2;
    
  char textbuf[FIELD_SIZE];

  param1_name = gtk_label_new (config_file->data->parameter_1.name);
  sprintf(textbuf, "%d", config_file->data->parameter_1.data_int_1);
  param1_1 = gtk_label_new (textbuf);

  sprintf(textbuf, "%d", config_file->data->parameter_1.data_int_2);
  param1_2 = gtk_label_new (textbuf);

  param2_name = gtk_label_new (config_file->data->parameter_2.name);

  sprintf(textbuf, "%d", config_file->data->parameter_2.data_int_1);
  param2_1 = gtk_label_new (textbuf);

  sprintf(textbuf, "%d", config_file->data->parameter_2.data_int_2);
  param2_2 = gtk_label_new (textbuf);

  grid = gtk_grid_new();

  gtk_grid_attach (GTK_GRID(grid), param1_name, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), param2_name, 0, 1, 1, 1);

  gtk_grid_attach (GTK_GRID(grid), param1_1, 1, 0, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), param2_1, 1, 1, 1, 1);

  gtk_grid_attach (GTK_GRID(grid), param1_2, 2, 0, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), param2_2, 2, 1, 1, 1);


  return (grid);
}


static void destroy_notepage_fileselect(GtkWidget *notepage_fs, FileData *config_file) {

  // g_free (config_file->filename_label); 
     // don't need to explicitly free this?
  // config file should already be closed by any function that accesses it (eg load_from_file)
  g_free (config_file->data);
  g_free (config_file);
  printf ("all memory associated with config_file freed\n");
}


static GtkWidget* create_notepage_fileselect() {

  GtkWidget *grid;
  GtkWidget *label1; // *label2;
  GtkWidget *file_select;
  GtkWidget *button_process_configfile;

  // first create memory for the file pointer
  FileData *config_file; // struct containing pointers to relevant file data
  config_file = g_malloc (sizeof(FileData)); 
  config_file->fp = NULL;


  char filename[FILENAME_MAX_LENGTH];
  strcpy (filename, "no file selected");
  config_file->filename_label = gtk_label_new(filename);

  config_file->data = g_malloc(sizeof(GenericParameterSet));
  init_generic_parameter_set(config_file->data);
      // in production version, data should not be a member of the file pointer as 
      // we want it to persist


  label1 = gtk_label_new("Select config file");
  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);
  
  file_select = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(file_select), 
				 "gtk_config_file.conf");
  g_signal_connect (file_select, "changed", G_CALLBACK(select_file), (gpointer)(config_file) );

  // aesthetic: give this a standard icon
  button_process_configfile = gtk_button_new_with_label ("Load from file");
  g_signal_connect (button_process_configfile, "clicked", 
		    G_CALLBACK(load_from_file), (gpointer)(config_file));

  grid = gtk_grid_new();
  gtk_grid_attach (GTK_GRID(grid), label1, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), file_select, 0, 1, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), config_file->filename_label, 0, 2, 1, 1);
  gtk_grid_attach (GTK_GRID(grid), button_process_configfile, 0, 3, 1, 1);
  
  gtk_grid_attach (GTK_GRID(grid), display_generic_parameter_data(config_file), 1, 0, 1, 4);

  gtk_widget_set_vexpand (GTK_WIDGET(grid), TRUE);


  
  gtk_widget_show_all(grid);

  g_signal_connect (G_OBJECT(grid), "destroy", 
		    G_CALLBACK (destroy_notepage_fileselect), 
		    (gpointer)config_file);

  // free config_file pointer here to prevent memory leak?
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
			   create_notepage_fileselect(), 
			   gtk_label_new("Config"));

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

