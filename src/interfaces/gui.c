#include "headers/gui.h"

extern char* serverip;
extern char* portnum;
extern char* connection;
extern char* partnerip;

GtkTextBuffer *buffer_messages;
GtkTextBuffer *buffer_entry;


static void start(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *scrolled_window;
    GtkWidget *view;
    GtkWidget *separator;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Encrypto");
    gtk_window_set_default_size (GTK_WINDOW (window), 360, 480);
    gtk_window_set_resizable(GTK_WINDOW (window), FALSE);

    grid = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (window), grid);

    view = gtk_label_new("Server: ");
    gtk_widget_set_size_request(view, 45, 50);
    gtk_grid_attach(GTK_GRID(grid), view, 0, 0, 2, 1);

    view = gtk_label_new(serverip);
    gtk_widget_set_size_request(view, 45, 50);
    gtk_grid_attach(GTK_GRID(grid), view, 2, 0,2, 1);

    view = gtk_label_new("Port: ");
    gtk_widget_set_size_request(view, 45, 50);
    gtk_grid_attach(GTK_GRID(grid), view, 4, 0,2, 1);

    view = gtk_label_new(portnum);
    gtk_widget_set_size_request(view, 45, 50);
    gtk_grid_attach(GTK_GRID(grid), view, 6, 0,2, 1);

    view = gtk_label_new("Status: ");
    gtk_widget_set_size_request(view, 45, 50);
    gtk_grid_attach(GTK_GRID(grid), view, 0, 1,2, 1);


    view = gtk_label_new(connection);
    gtk_widget_set_size_request(view, 45, 50);
    gtk_grid_attach(GTK_GRID(grid), view, 2, 1,2, 1);


    view = gtk_label_new("Partner: ");
    gtk_widget_set_size_request(view, 45, 50);
    gtk_grid_attach(GTK_GRID(grid), view, 4, 1,2, 1);


    view = gtk_label_new(partnerip);
    gtk_widget_set_size_request(view, 45, 50);
    gtk_grid_attach(GTK_GRID(grid), view, 6, 1,2, 1);

    separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_grid_attach(GTK_GRID(grid), separator, 0, 2, 8, 1);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 10);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_window, 360, 400);
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 3, 8, 1);

    view = gtk_text_view_new ();
    buffer_messages = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    gtk_text_buffer_set_text (buffer_messages, "<Place for messages>", -1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view), FALSE);
    gtk_widget_set_size_request(view, 350, 390);
    gtk_container_add(GTK_CONTAINER(scrolled_window), view);

    separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_grid_attach(GTK_GRID(grid), separator, 0, 4, 8, 1);


    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 10);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_window, 360, 80);
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 5, 7, 5);


    view = gtk_text_view_new ();
    buffer_entry = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    gtk_text_buffer_set_text (buffer_entry, "<Place for input>", -1);
    gtk_widget_set_size_request(view, 350, 70);
    gtk_container_add(GTK_CONTAINER(scrolled_window), view);

    button = gtk_button_new_with_label ("Send");
    g_signal_connect (button, "clicked", G_CALLBACK (send_clicked), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 7, 7, 1, 1);


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

void send_clicked()
{
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer_entry, &start, &end);
    gchar *text = gtk_text_buffer_get_text(buffer_entry, &start, &end, FALSE));
    write_comm(&i_miso, text);
    g_free(text);
    gtk_text_buffer_set_text(buffer_entry, "", -1);
}