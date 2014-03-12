
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include "string_parse.h"

#define CONFIG_FILE gtk_config_file.conf


typedef struct display_widgets {

  GtkWidget *param1_name;
  GtkWidget *param1_1;
  GtkWidget *param1_2;

  GtkWidget *param2_name;
  GtkWidget *param2_1;
  GtkWidget *param2_2;

} DisplayWidgets;





// callback function to read file contents
gboolean load_from_file (GtkWidget *widget, FileData *file_info) {

  file_info->fp = fopen(file_info->filename, "r");
  if (file_info->fp == NULL) {
    printf ("error! gtk_config_file.conf does not exist\n");
    return FALSE;
  }
  else {
    printf ("success! config file opened.\n");

    pdp_file_parse_to_treestore (file_info);

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



static void destroy_notepage_fileselect(GtkWidget *notepage_fs, FileData *config_file) {

  // g_free (config_file->filename_label); 
     // don't need to explicitly free this?
  // config file should already be closed by any function that accesses it (eg load_from_file)
  // g_free (config_file->data);
  g_free (config_file);
  printf ("all memory associated with config_file freed\n");
}



FileData * init_config_file (GtkTreeStore * tree_store){

  // first create memory for the file pointer
  FileData *config_file; // struct containing pointers to relevant file data
  config_file = g_malloc (sizeof(FileData)); 
  config_file->fp = NULL;

  char filename[FILENAME_MAX_LENGTH];
  strcpy (filename, "no file selected");
  config_file->filename_label = gtk_label_new(filename);
  
  config_file->tree_store = tree_store;

  return config_file;
}


// selection handling
// prototype for selection handler callback
static void config_file_treeview_selection_changed_cb (GtkTreeSelection *selection, gpointer data) {

  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *param_name;
  gchar *param_value;

  if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
    gtk_tree_model_get (model, &iter, COL_PARAMETER_NAME, &param_name, -1);
    gtk_tree_model_get (model, &iter, COL_PARAMETER_VALUE, &param_value, -1);
    g_print ("%s: %s\n", param_name, param_value);
    g_free (param_name);
    g_free (param_value);
    
  }
}


static void setup_config_file_treeview (GtkTreeView * tree) {

  GtkTreeViewColumn *column;
  GtkCellRenderer *renderer;

  // aesthetic properties:
  gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(tree), TRUE);


  // create a cell renderer, arbitrarily make it red for demonstration purposes
  renderer = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (renderer), "foreground", "red", NULL);

  // create a column, associate the "text" attribute of the cell renderer to the
  // first column of the model, parameter name
  column = gtk_tree_view_column_new_with_attributes ("Parameter", renderer,
						     "text", COL_PARAMETER_NAME,
						     NULL);

  // add the column to the view
  gtk_tree_view_append_column (GTK_TREE_VIEW(tree), column);

  // second column... parameter value
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Value", renderer, "text",
						     COL_PARAMETER_VALUE,
						     NULL);

  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);


  // set up the selection handler
  GtkTreeSelection *select;

  select = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree));
  gtk_tree_selection_set_mode (select, GTK_SELECTION_SINGLE);

  g_signal_connect (G_OBJECT(select), "changed", 
		    G_CALLBACK(config_file_treeview_selection_changed_cb), NULL);

}



static GtkWidget* create_notepage_fileselect() {

  GtkWidget *grid_main;
  GtkWidget *grid_controls;
  GtkWidget *label1; // *label2;
  GtkWidget *file_select;
  GtkWidget *button_process_configfile;

  // create a treestore to store parsed data
  GtkTreeStore *store;
  GtkWidget *tree;

  store = gtk_tree_store_new (N_COLUMNS,
			      G_TYPE_STRING,
			      G_TYPE_STRING);

  // create a view
  tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));

  // view now holds a reference. Get rid of our own reference:
  g_object_unref (G_OBJECT (store));

  // setup tree view
  setup_config_file_treeview (GTK_TREE_VIEW(tree));
  
  // setup config file data  
  FileData * config_file = init_config_file(GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree))));


  label1 = gtk_label_new("Select config file");
  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);
  
  file_select = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(file_select), 
				 "gtk_config_file_1.conf");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(file_select), 
				 "gtk_config_file_2.conf");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(file_select), 
				 "pdpgui_gs_params_default.conf");
  g_signal_connect (file_select, "changed", G_CALLBACK(select_file), (gpointer)(config_file) );

  // aesthetic: give this a standard icon
  button_process_configfile = gtk_button_new_with_label ("Load from file");
  g_signal_connect (button_process_configfile, "clicked", 
		    G_CALLBACK(load_from_file), (gpointer)(config_file));

  grid_main = gtk_grid_new();
  grid_controls = gtk_grid_new();

  gtk_grid_attach (GTK_GRID(grid_controls), label1, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID(grid_controls), file_select, 0, 1, 1, 1);
  gtk_grid_attach (GTK_GRID(grid_controls), config_file->filename_label, 0, 2, 1, 1);
  gtk_grid_attach (GTK_GRID(grid_controls), button_process_configfile, 0, 3, 1, 1);
  //  gtk_widget_set_vexpand (GTK_WIDGET(grid_controls), TRUE);
  
  gtk_grid_attach (GTK_GRID(grid_main), grid_controls, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID(grid_main), tree, 1, 0, 1, 1);
  gtk_grid_set_column_spacing (GTK_GRID(grid_main), 30);
  gtk_widget_set_vexpand (GTK_WIDGET(grid_main), TRUE);
  gtk_widget_set_hexpand (GTK_WIDGET(grid_main), TRUE);


  gtk_widget_show_all(grid_main);

  g_signal_connect (G_OBJECT(grid_main), "destroy", 
		    G_CALLBACK (destroy_notepage_fileselect), 
		    (gpointer)config_file);

  return (grid_main);
  
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

