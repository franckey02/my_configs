#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static void close_session_cb(GtkWidget *widget, gpointer data) {
  system("openbox --exit");
}

static void shutdown_cb(GtkWidget *widget, gpointer data) {
  system("systemctl poweroff");
}

static void reboot_cb(GtkWidget *widget, gpointer data) {
  system("systemctl reboot");
}

int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *button_close_session;
  GtkWidget *button_shutdown;
  GtkWidget *button_reboot;
  GtkWidget *hbox; 
  GtkWidget *label_title;
  GdkPixbuf *icon;

  gtk_init(&argc, &argv);

// Carga el icono desde el archivo log.ico
  icon = gdk_pixbuf_new_from_file("/usr/share/icons/log.ico", NULL);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "JaviOS"); 
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
 // Establece el icono de la ventana
  gtk_window_set_icon(GTK_WINDOW(window), icon);
  // Centrar la ventana en la pantalla
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); 
  gtk_container_add(GTK_CONTAINER(window), hbox);

  // Título de la ventana (con estilo)
  label_title = gtk_label_new("JaviOS");
  gtk_label_set_justify(GTK_LABEL(label_title), GTK_JUSTIFY_CENTER);
  PangoFontDescription *font_desc = pango_font_description_new();
  pango_font_description_set_family(font_desc, "Ontel"); 
  pango_font_description_set_size(font_desc, 30 * PANGO_SCALE); 
  gtk_widget_override_font(label_title, font_desc);
  pango_font_description_free(font_desc);
  gtk_box_pack_start(GTK_BOX(hbox), label_title, FALSE, FALSE, 10);


  // Botón Cerrar Sesión con icono (cuadrado)
  button_close_session = gtk_button_new();
  GtkWidget *image_close_session = gtk_image_new_from_icon_name("system-log-out", GTK_ICON_SIZE_LARGE_TOOLBAR); // Cambiado a GTK_ICON_SIZE_LARGE_TOOLBAR
  gtk_button_set_image(GTK_BUTTON(button_close_session), image_close_session);
  gtk_button_set_label(GTK_BUTTON(button_close_session), "Cerrar Sesión");
  g_signal_connect(button_close_session, "clicked", G_CALLBACK(close_session_cb), NULL);
  gtk_widget_set_size_request(button_close_session, 150, 150); 
  gtk_box_pack_start(GTK_BOX(hbox), button_close_session, TRUE, TRUE, 0);

  // Botón Apagar con icono (cuadrado)
  button_shutdown = gtk_button_new();
  GtkWidget *image_shutdown = gtk_image_new_from_icon_name("system-shutdown", GTK_ICON_SIZE_LARGE_TOOLBAR); // Cambiado a GTK_ICON_SIZE_LARGE_TOOLBAR
  gtk_button_set_image(GTK_BUTTON(button_shutdown), image_shutdown);
  gtk_button_set_label(GTK_BUTTON(button_shutdown), "Apagar");
  g_signal_connect(button_shutdown, "clicked", G_CALLBACK(shutdown_cb), NULL);
  gtk_widget_set_size_request(button_shutdown, 150, 150); 
  gtk_box_pack_start(GTK_BOX(hbox), button_shutdown, TRUE, TRUE, 0);

  // Botón Reiniciar con icono (cuadrado)
  button_reboot = gtk_button_new();
  GtkWidget *image_reboot = gtk_image_new_from_icon_name("system-reboot", GTK_ICON_SIZE_LARGE_TOOLBAR); // Cambiado a GTK_ICON_SIZE_LARGE_TOOLBAR
  gtk_button_set_image(GTK_BUTTON(button_reboot), image_reboot);
  gtk_button_set_label(GTK_BUTTON(button_reboot), "Reiniciar");
  g_signal_connect(button_reboot, "clicked", G_CALLBACK(reboot_cb), NULL);
  gtk_widget_set_size_request(button_reboot, 150, 150); 
  gtk_box_pack_start(GTK_BOX(hbox), button_reboot, TRUE, TRUE, 0);

  gtk_widget_show_all(window);
  gtk_main();
  g_object_unref(icon); // Libera el pixbuf

  return 0;
}