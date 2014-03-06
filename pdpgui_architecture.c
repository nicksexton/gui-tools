#include <gtk/gtk.h>
#include <pango/pangocairo.h>
#include "pdpgui_draw.h"
#include "lib_cairox.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


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

// example drawing callback function
void pdpgui_draw_example_network (GtkWidget *widget, cairo_t *cr, gpointer data) {

  double activation_a1, activation_a2, activation_a3, activation_b1, activation_b2;

  // set locations of units to draw 
  PdpguiCoords location_a1 = { .x = 300, .y = 400};
  PdpguiCoords location_a2 = { .x = 400, .y = 400};
  PdpguiCoords location_a3 = { .x = 500, .y = 400};

  PdpguiCoords location_b1 = { .x = 350, .y = 200};
  PdpguiCoords location_b2 = { .x = 450, .y = 200};

  // set control points for curved connections
  // PdpguiCoords location_control1 = { .x = 400, .y = 266};
  // PdpguiCoords location_control2 = { .x = 400, .y = 333};


  // set activation of units
  activation_a1 = 0.1;
  activation_a2 = 0.25;
  activation_a3 = 0.85;

  activation_b1 = 0.0;
  activation_b2 = 0.9;


  // set unit colours
  PdpguiColourRgb a_colour_on = { .r = 0.9, .g = 0.1, .b = 0.1};
  PdpguiColourRgb a_colour_off = { .r = 0.1, .g = 0.1, .b = 0.1};

  PdpguiColourRgb b_colour_on = { .r = 0.15, .g = 0.1, .b = 0.9};
  PdpguiColourRgb b_colour_off = { .r = 0.15, .g = 0.1, .b = 0.3};

  
  // set colour for background
  cairo_set_source_rgb (cr, 1, 1, 1);
  // fill background colour
  cairo_paint (cr);

  // draw layer 1
  pdpgui_draw_unit (cr, location_a1, a_colour_off, a_colour_on, activation_a1);
  pdpgui_draw_unit (cr, location_a2, a_colour_off, a_colour_on, activation_a2);
  pdpgui_draw_unit (cr, location_a3, a_colour_off, a_colour_on, activation_a3);


  // draw layer 2
  pdpgui_draw_unit (cr, location_b1, b_colour_off, b_colour_on, activation_b1);
  pdpgui_draw_unit (cr, location_b2, b_colour_off, b_colour_on, activation_b2);


  // draw connections (curved)
  pdpgui_draw_connection (cr, location_a1, location_b1);
  pdpgui_draw_connection (cr, location_a1, location_b2);

  pdpgui_draw_connection (cr, location_a2, location_b1);
  pdpgui_draw_connection (cr, location_a2, location_b2);

  pdpgui_draw_connection (cr, location_a3, location_b1);
  pdpgui_draw_connection (cr, location_a3, location_b2);

}

void pdpgui_draw_example_graph (GtkWidget *widget, cairo_t *cr, gpointer data) {

  // cairo_scale (cr, WINDOW_WIDTH, WINDOW_HEIGHT);
  // set colour for background
  // cairo_set_source_rgb (cr, 1, 1, 1);
  // fill background colour
  // cairo_paint (cr);

  pdpgui_draw_graph_axes(cr, 10, 10, 0.0, 200.0, 0.0, 1.0);



}

/*
// Test pango layout
static void pango_layout (GtkWidget *widget, cairo_t *cr, gpointer data) {

  PangoLayout *layout;
  CairoxTextParameters text_params;
  char textbuf[160];
  
  layout = pango_cairo_create_layout (cr);

  // set colour for background
  cairo_set_source_rgb (cr, 1, 1, 1);
  // fill background colour
  cairo_paint (cr);

  g_snprintf (textbuf, 160, "Labyrinth");

  // print large
  pangox_layout_set_font_size (layout, 15);

  cairox_text_parameters_set (&text_params, 50, 50, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_TOP, 0.0);
  cairox_text_parameters_set_foreground (&text_params, 1, 0, 0);
  cairox_paint_pango_text (cr, &text_params, layout, textbuf);


  // print small
  pangox_layout_set_font_size (layout, 10);

  cairox_text_parameters_set (&text_params, 50, 100, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_TOP, 0.0);
  cairox_text_parameters_set_foreground (&text_params, 1, 0, 0);
  cairox_paint_pango_text (cr, &text_params, layout, textbuf);


  // print many
  
  int i;

  for (i = 0; i < 10; i ++) {
    cairox_text_parameters_set (&text_params, 
				50 + (i * 50), 
				(150 + i * 50), 
				PANGOX_XALIGN_LEFT, PANGOX_YALIGN_TOP, 0.0);
  cairox_text_parameters_set_foreground (&text_params, 1, 0, 0);
  cairox_paint_pango_text (cr, &text_params, layout, textbuf);
  }

  pango_cairo_show_layout(cr, layout);


}
*/


static GtkWidget* create_notepage_architecture() {
  // creates a notepage that contains a drawing area
  GtkWidget *grid;
  GtkWidget *drawing_area;
  GtkWidget *label;

  label = gtk_label_new ("Network Architecture");

  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT);
  g_signal_connect (drawing_area, "draw", G_CALLBACK(pdpgui_draw_example_network), NULL);

  grid = gtk_grid_new();
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), drawing_area, 0, 1, 1, 1);

  return (grid);

}

static GtkWidget* create_notepage_graph() {
  // example notepage that draws a graph (eg., of network activation during a trial)

  GtkWidget *grid;
  GtkWidget *drawing_area;
  GtkWidget *label;

  label = gtk_label_new ("Network Activation");

  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT);
  g_signal_connect (drawing_area, "draw", G_CALLBACK(pdpgui_draw_example_graph), NULL);
  // g_signal_connect (drawing_area, "draw", G_CALLBACK(pango_layout), NULL);

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
			   create_notepage_graph(), 
			   gtk_label_new("Graph Activation"));
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

