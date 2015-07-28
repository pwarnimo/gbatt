#include <gtk/gtk.h>
#include "about.h"

void trayIconClick(GtkStatusIcon *icon, gpointer data) {
	printf("Clicked on tray icon\n");
}

void popupMenuClick(GtkStatusIcon *icon, guint button, guint activateTime, gpointer data) {
	printf("Popup menu");
}

int showPopupMenu(GtkWidget *widget, GdkEvent *event) {
	const gint RIGHT_CLICK = 3;
	
	if (event->type == GDK_BUTTON_PRESS) {
		GdkEventButton *bevent = (GdkEventButton *) event;

      if (bevent->button == RIGHT_CLICK) {      
          
      	gtk_menu_popup(GTK_MENU(widget), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
		}
          
   	return TRUE;
	}

	return FALSE;
}

static GtkStatusIcon *createTrayIcon() {
	GtkStatusIcon *trayIcon;

	trayIcon = gtk_status_icon_new();

	g_signal_connect(G_OBJECT(trayIcon), "activate", G_CALLBACK(trayIconClick), NULL);

	GdkPixbuf *sprite;
	GdkPixbuf *current;

	sprite = gdk_pixbuf_new_from_file("res/battery-sprite.png", NULL);

	current = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 16, 16);

	gdk_pixbuf_copy_area(sprite, 0, 0, 16, 16, current, 0, 0);

	//GdkPixbuf("res/battery-sprite.png", NULL);

	//gtk_status_icon_set_from_icon_name(trayIcon, GTK_STOCK_MEDIA_STOP);
	gtk_status_icon_set_from_pixbuf(trayIcon, current);
	gtk_status_icon_set_tooltip(trayIcon, "Battery (bat0) is discharging: 100%");
	gtk_status_icon_set_visible(trayIcon, TRUE);

	return trayIcon;
}

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkStatusIcon *trayIcon;

	GtkWidget *popupMenu;
	GtkWidget *hideWindow;
	GtkWidget *quitApplication;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_title(GTK_WINDOW(window), "GBatt 0.1");

	popupMenu = gtk_menu_new();

	hideWindow = gtk_menu_item_new_with_label("Minimize");
	gtk_widget_show(hideWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(popupMenu), hideWindow);

	quitApplication = gtk_menu_item_new_with_label("Quit");
	gtk_widget_show(quitApplication);
	gtk_menu_shell_append(GTK_MENU_SHELL(popupMenu), quitApplication);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	trayIcon = createTrayIcon();

	g_signal_connect_swapped(G_OBJECT(trayIcon), "button-press-event", G_CALLBACK(showPopupMenu), popupMenu);

	gtk_widget_show(window);

	showAboutDialog((gpointer)window, NULL);

	gtk_main();

	return 0;
}
