#include <gtk/gtk.h>
#include "pdpgui_draw.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300



// example drawing callback function
void pdpgui_draw_example (GtkWidget *widget, cairo_t *cr, gpointer data) {

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


static GtkWidget* create_notepage_architecture() {
  // creates a notepage that contains a drawing area
  GtkWidget *grid;
  GtkWidget *drawing_area;
  GtkWidget *label;

  label = gtk_label_new ("Network Architecture");

  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT);
  g_signal_connect (drawing_area, "draw", G_CALLBACK(pdpgui_draw_example), NULL);

  grid = gtk_grid_new();
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), drawing_area, 0, 1, 1, 1);

  return (grid);

}

static GtkWidget* create_notepage_zinc() {

  GtkWidget *grid;
  GtkWidget *label1;

  label1 = gtk_label_new("Zinc is a moderately reactive, blue gray metal \
that tarnishes in moist air and burns in air with a bright blueish-green flame,\
giving off fumes of zinc oxide. It reacts with acids, alkalis and other non-metals.\
If not completely pure, zinc reacts with dilute acids to release hydrogen.");

  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);

  grid = gtk_grid_new();
  gtk_grid_attach (GTK_GRID(grid), label1, 0, 0, 1, 1);
  gtk_widget_set_vexpand (GTK_WIDGET(grid), TRUE);

  gtk_widget_show_all(grid);
  return (grid);

}


static GtkWidget* create_notepage_copper() {

  GtkWidget *grid;
  GtkWidget *label1;

  label1 = gtk_label_new("Copper is an essential trace nutrient to all high \
plants and animals. In animals, including humans, it is found primarily in \
the bloodstream, as a co-factor in various enzymes, and in copper-based pigments. \
However, in sufficient amounts, copper can be poisonous and even fatal to organisms.");

  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);

  grid = gtk_grid_new();
  gtk_grid_attach (GTK_GRID(grid), label1, 0, 0, 1, 1);
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
  // connect button callback here!
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
			   create_notepage_architecture(), 
			   gtk_label_new("Architecture"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notes), 
			   create_notepage_zinc(), 
			   gtk_label_new("Zinc"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notes), 
			   create_notepage_copper(), 
			   gtk_label_new("Copper"));


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

