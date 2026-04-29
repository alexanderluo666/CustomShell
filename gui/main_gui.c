#include <gtk/gtk.h>
#include "../core/engine.h"

GtkWidget *text_view;
GtkTextBuffer *buffer;

void on_run(GtkButton *btn, gpointer entry_ptr) {
    GtkEntry *entry = GTK_ENTRY(entry_ptr);
    const char *input = gtk_entry_get_text(entry);

    char output[2048] = "";
    execute_command(input, output);

    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, output, -1);
    gtk_text_buffer_insert(buffer, &iter, "\n", -1);
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "CustomShell GUI");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *entry = gtk_entry_new();
    GtkWidget *btn = gtk_button_new_with_label("Run");

    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), text_view, TRUE, TRUE, 0);

    g_signal_connect(btn, "clicked", G_CALLBACK(on_run), entry);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}
