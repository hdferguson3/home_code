#include <stdio.h>
#include "temp_humidity_v2.h"
#include <gtk-3.0/gtk/gtk.h>
#include <time.h>

static void _quit_cb (GtkWidget *button, gpointer data);
//static gboolean _label_update(gpointer data);
 
static void
_quit_cb (GtkWidget *button, gpointer data)
{
    (void)button; (void)data; /*Avoid compiler warnings*/
    gtk_main_quit();
    return;
}

static gboolean
_label_update(gpointer data)
{
    GtkLabel *label = (GtkLabel*)data;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    gtk_label_set_label(label, out_string );
    //gtk_label_set_label(label, asctime (timeinfo) );
    //printf("%s", out_string);
    /* Restart the timer */
    return TRUE;
 
}
 
int main(void)
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *quit_button;
    GtkWidget *label;
 
    gtk_init(NULL, NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 200, 100);
    g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);
    vbox = gtk_box_new (FALSE, 2);
    gtk_container_add(GTK_CONTAINER(window), vbox);
 
    quit_button = gtk_button_new_with_label("Quit");
    g_signal_connect(G_OBJECT(quit_button), "clicked", G_CALLBACK(_quit_cb), NULL);
   
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    label = gtk_label_new(asctime (timeinfo) );
    /* 250ms update */
    g_timeout_add(250, _label_update, label);
    
    gtk_box_pack_start (GTK_BOX(vbox), label, 0, 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), quit_button, 0, 0, 0);
   
    gtk_widget_show_all(window);
     
	gtk_main();
	
	dht_loop();
    
    return 0;
}

