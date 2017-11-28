#include "headers/gui.h"

static void start(GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Encrypto");
  gtk_window_set_default_size (GTK_WINDOW (window), 360, 480);
  gtk_window_set_resizable(GTK_WINDOW (window), FALSE);
  gtk_widget_show_all (window);
}



void* gui(void* params)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("hu.bme.xao5er.encrypto", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (start), NULL);
  status = g_application_run (G_APPLICATION (app), 0, NULL);
  g_object_unref (app);
}