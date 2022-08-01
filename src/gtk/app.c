/**
 * app.c
 * Main entry point for the pretty GTK GUI application.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "app.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * GTK application's main entry point.
 *
 * @param  argc Number of command line arguments passed to us.
 * @param  argv Command line arguments.
 * @return      0 on success.
 */
int app_main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
	GtkBuilder *builder;
	GError *error = NULL;

	// Initialize GTK.
	gtk_init(NULL, NULL);

	// Start building our GUI.
	builder = gtk_builder_new();
	if (gtk_builder_add_from_resource(builder, "/com/innoveworkshop/Pecan/main_window.glade", &error) == 0) {
		g_printerr("Error loading Glade resource: %s\n", error->message);
		g_clear_error(&error);
		return 1;
	}

	// Attach a simple Quit signal handler to the main window.
	GObject *window = gtk_builder_get_object(builder, "main_window");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);

	// Run the main application loop.
	gtk_main();
	return 0;
}

