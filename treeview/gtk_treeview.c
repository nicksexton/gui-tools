#include <gtk/gtk.h>


enum {
  TITLE_COLUMN,
  AUTHOR_COLUMN,
  CHECKED_COLUMN,
  N_COLUMNS
};


static void populate_tree_model (GtkTreeStore * store) {

  GtkTreeIter iter1; // parent iterator
  GtkTreeIter iter2; // child iterator

  gtk_tree_store_append (store, &iter1, NULL); // acquire a top-level iterator

  gtk_tree_store_set (store, &iter1,
		      TITLE_COLUMN, "The Art of Computer Programming", 
		      AUTHOR_COLUMN, "Donald E. Knuth",
		      CHECKED_COLUMN, FALSE,
		      -1); // -1 used to indicate end of data
  
  gtk_tree_store_append (store, &iter2, &iter1); // acquire a child iterator
  gtk_tree_store_set (store, &iter2,
		      TITLE_COLUMN, "Volume 1: Fundamental Algorithms", 
		      -1); 

  gtk_tree_store_append (store, &iter2, &iter1);
  gtk_tree_store_set (store, &iter2,
		      TITLE_COLUMN, "Volume 2: Seminumerical Algorithms", 
		      -1); 

  gtk_tree_store_append (store, &iter2, &iter1);
  gtk_tree_store_set (store, &iter2,
		      TITLE_COLUMN, "Volume 3: Sorting and Searching", 
		      -1); 

  gtk_tree_store_append (store, &iter1, NULL); // acquire a top-level iterator
  gtk_tree_store_set (store, &iter1,
		      TITLE_COLUMN, "Parallel Distributed Processing", 
		      AUTHOR_COLUMN, "Rumelhart, D., McClelland, J., The PDP Research Group",
		      CHECKED_COLUMN, FALSE,
		      -1); // -1 used to indicate end of data


  gtk_tree_store_append (store, &iter2, &iter1); // acquire a child iterator
  gtk_tree_store_set (store, &iter2,
		      TITLE_COLUMN, "Volume 1: Foundations", 
		      CHECKED_COLUMN, TRUE,
		      -1); 

  gtk_tree_store_append (store, &iter2, &iter1); // acquire a child iterator
  gtk_tree_store_set (store, &iter2,
		      TITLE_COLUMN, "Volume 2: Psychological and Biological Models", 
		      -1); 


}


// selection handling
// prototype for selection handler callback
static void tree_selection_changed_cb (GtkTreeSelection *selection, gpointer data) {

  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *author;

  if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
    gtk_tree_model_get (model, &iter, AUTHOR_COLUMN, &author, -1);
    g_print ("You selected a book by %s\n", author);
    g_free (author);
  }

}



// returns a Treestore 
static GtkWidget * create_treestore () {

  GtkTreeStore *store;
  GtkWidget *tree;


  GtkTreeViewColumn *column;
  GtkCellRenderer *renderer;

  store = gtk_tree_store_new (N_COLUMNS,
			      G_TYPE_STRING,
			      G_TYPE_STRING,
			      G_TYPE_BOOLEAN);

  // custom function to fill the model with data
  populate_tree_model (store);

  // create a view
  tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));

  // view now holds a reference. Get rid of our own reference:
  g_object_unref (G_OBJECT (store));

  // create a cell renderer, arbitrarily make it red for demonstration purposes
  renderer = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (renderer), "foreground", "red", NULL);

  // create a column, associate the "text" attribute of the cell renderer to the
  // first column of the model
  column = gtk_tree_view_column_new_with_attributes ("Author", renderer,
						     "text", AUTHOR_COLUMN,
						     NULL);

  // add the column to the view
  gtk_tree_view_append_column (GTK_TREE_VIEW(tree), column);

  // second column... title of the book
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Title", renderer, "text",
						     TITLE_COLUMN,
						     NULL);

  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

  // last column... whenever a book is checked out
  renderer = gtk_cell_renderer_toggle_new ();
  column = gtk_tree_view_column_new_with_attributes ("Checked out", renderer, "active",
						     CHECKED_COLUMN,
						     NULL);

  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);



  // set up the selection handler
  GtkTreeSelection *select;

  select = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree));
  gtk_tree_selection_set_mode (select, GTK_SELECTION_SINGLE);
  g_signal_connect (G_OBJECT(select), "changed", G_CALLBACK(tree_selection_changed_cb), NULL);

  return tree;

}



static GtkWidget* create_notepage_treeview() {

  GtkWidget *grid;
  GtkWidget *tree;

  // create a model. Using the store model for now, though
  // could use any GtkTreeModel

  tree = create_treestore ();



  grid = gtk_grid_new();

  gtk_grid_attach (GTK_GRID(grid), tree, 0, 0, 1, 1);
  // attach some widgets to the grid

  gtk_widget_show_all(grid);
  return (grid);

}

  
static void activate(GtkApplication *app, gpointer user_data) {

  GtkWidget *window;
  GtkWidget *grid;


  GtkWidget *notes;


  // Create a window with a title, default size, and set border width
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW(window), "GUI: notebook");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER(window), 10);
  

  // ------------- NOTEPAD -----------------

  notes = gtk_notebook_new();
  gtk_notebook_append_page(GTK_NOTEBOOK(notes), 
			   create_notepage_treeview(), 
			   gtk_label_new("Treeview"));


  // Create a full-window grid to contain toolbar and the notebook
  grid = gtk_grid_new();
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

