#include "../headers/gui.h"


static void notify(gpointer data);
static gboolean rerender(gpointer data);
static void openDialog();
static void nextRender();
static void onOpenActivate(GtkMenuItem *item, gpointer userData);
static void onImproveActivate(GtkMenuItem *item, gpointer userData);

static GtkWidget *mainWindow;
static GtkWidget *drawingArea;
static bool pendingRender = false;
static image img = {IMAGE_INIT_WIDTH/10, IMAGE_INIT_HEIGHT/10, NULL, false};

void activate(GtkApplication *app, gpointer userData) {
    mainWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(mainWindow), WINDOW_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(mainWindow),
                                IMAGE_INIT_WIDTH * PIXEL_WIDTH,
                                IMAGE_INIT_HEIGHT * PIXEL_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(mainWindow), FALSE);

    GtkWidget *vBoxContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(mainWindow), vBoxContainer);

    /* ---  menu bar --- */
    GtkWidget *menuBar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vBoxContainer), menuBar, FALSE, FALSE, 0);

    /* menu "File" */
    GtkWidget *fileMenu = gtk_menu_new();

    GtkWidget *fileItem = gtk_menu_item_new_with_mnemonic("_File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileItem), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), fileItem);

    GtkWidget *openItem = gtk_menu_item_new_with_mnemonic("_Open...");
    g_signal_connect(openItem, "activate", G_CALLBACK(onOpenActivate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openItem);

    GtkWidget *quitItem = gtk_menu_item_new_with_mnemonic("_Quit");
    g_signal_connect_swapped(quitItem, "activate", G_CALLBACK(gtk_widget_destroy), mainWindow);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitItem);

    /* menu "Render" */
    GtkWidget *renderMenu = gtk_menu_new();

    GtkWidget *renderItem = gtk_menu_item_new_with_mnemonic("_Render");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(renderItem), renderMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), renderItem);

    GtkWidget *improveItem = gtk_menu_item_new_with_mnemonic("_Improve quality");
    g_signal_connect(improveItem, "activate", G_CALLBACK(onImproveActivate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(renderMenu), improveItem);

    /* --- drawing area --- */
    drawingArea = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingArea, IMAGE_INIT_WIDTH * PIXEL_WIDTH, IMAGE_INIT_HEIGHT * PIXEL_HEIGHT);
    gtk_box_pack_start(GTK_BOX(vBoxContainer), drawingArea, TRUE, TRUE, 0);
    g_signal_connect(drawingArea, "draw", G_CALLBACK(draw), &img);

    gtk_widget_show_all(mainWindow);
}

static void onOpenActivate(GtkMenuItem *item, gpointer userData) {
    openDialog();
}

static void onImproveActivate(GtkMenuItem *item, gpointer userData) {
    nextRender();
}

void openDialog() {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open .obj file",
                                                    GTK_WINDOW(mainWindow),
                                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "Cancel",
                                                    GTK_RESPONSE_CANCEL,
                                                    "Open",
                                                    GTK_RESPONSE_ACCEPT,
                                                    NULL);
    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        img.render = load(filename);
        img.imageWidth = IMAGE_INIT_WIDTH / 10;
        img.imageHeight = IMAGE_INIT_HEIGHT / 10;
        pendingRender = true;
        gdk_threads_add_idle_full(G_PRIORITY_DEFAULT, rerender, &img, notify);
    }
    gtk_widget_destroy(dialog);
}

void nextRender() {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(mainWindow),
                                               0,
                                               GTK_MESSAGE_QUESTION,
                                               GTK_BUTTONS_OK_CANCEL,
                                               "%s",
                                               "Are you sure you want to rerender object with better resolution? It may take a while.");

    if (!pendingRender) {
        gint res = gtk_dialog_run(GTK_DIALOG(dialog));
        if (res == GTK_RESPONSE_OK) {
            img.imageWidth = IMAGE_INIT_WIDTH;
            img.imageHeight = IMAGE_INIT_HEIGHT;
            pendingRender = true;
            gdk_threads_add_idle_full(G_PRIORITY_DEFAULT, rerender, &img, notify);
        }
    }
    gtk_widget_destroy(dialog);
}

void notify(gpointer data) {
    pendingRender = false;
}

gboolean rerender(gpointer data) {
    Image i = data;
    if (i->buffer != NULL)
        free(i->buffer);
    i->buffer = render(i->imageWidth, i->imageHeight);
    gtk_widget_queue_draw(drawingArea);
    return FALSE;
}
