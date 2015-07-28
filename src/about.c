#include "about.h"

void showAboutDialog(GtkWidget *widget, gpointer data) {
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("res/battery.png", NULL);
	GtkWidget *dialog = gtk_about_dialog_new();

	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "GBatt");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.1");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright (C) 2015  Pol Warnimont");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "GBatt is a simple battery monitoring application.");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "https://github.com/pwarnimo/gbatt");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);

	g_object_unref(pixbuf), pixbuf = NULL;

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
