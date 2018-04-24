#include <gtk-3.0/gtk/gtk.h>
#include "temp_humidity_v2.h"

extern char out_string[1000];
char msg[1000]={0};

int main(int argc, char *argv[]) {
    
  GtkWidget *window;
  GtkWidget *label;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);
  gtk_window_set_title(GTK_WINDOW(window), "Markup label");

  g_snprintf(msg, sizeof msg, "Initializing... %s", out_string); //insert out_string -> msg

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), msg);
  
  gtk_container_add(GTK_CONTAINER(window), label);
  gtk_widget_show(label);

  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show(window);
  
  delay( 2000 );
  
  int loop();
  
  g_snprintf(msg, sizeof msg, "Waiting for data... %s", out_string); //insert out_string -> msg
 
  gtk_label_set_markup(GTK_LABEL(label), msg);

  gtk_main();
  
  return 0;
}
