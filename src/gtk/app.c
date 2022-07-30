/**
 * app.c
 * Main entry point for the pretty GTK GUI application.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "app.h"
#include <stdio.h>
#include <stdlib.h>

static void activate(GtkApplication* app, __attribute__((unused)) gpointer user_data) {
	GtkWidget *window;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Pecan");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_widget_show_all(window);
}

/**
 * GTK application's main entry point.
 *
 * @param  argc Number of command line arguments passed to us.
 * @param  argv Command line arguments.
 * @return      0 on success.
 */
int app_main(int argc, char **argv) {
	GtkApplication *app;
	int status;

	// Initialize the GTK application.
	app = gtk_application_new("com.innoveworkshop.pecan", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), 1, argv);  // Ignore arguments.
	g_object_unref(app);

	return status;
}

