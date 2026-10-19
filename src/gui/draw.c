#include "../headers/gui.h"

#define BLACK 0.0, 0.0, 0.0
#define WHITE 1.0, 1.0, 1.0
#define COLOR(x) (x), (x), (x)

void draw(GtkWidget *widget, cairo_t *c, gpointer userData) {
    Image image = userData;

    double windowWidth = gtk_widget_get_allocated_width(widget);
    double windowHeight = gtk_widget_get_allocated_height(widget);
    double pixelWidth = windowWidth / image->imageWidth;
    double pixelHeight = windowHeight / image->imageHeight;

    if (!image->render) {
        cairo_set_source_rgb(c, BLACK);
        cairo_rectangle(c, 0, 0, windowWidth, windowHeight);
        cairo_fill(c);
    } else {
        for (int x = 0; x < image->imageWidth; x++) {
            for (int y = 0; y < image->imageHeight; y++) {
                cairo_set_source_rgb(c, COLOR(image->buffer[bufferIndex(x, y, image->imageWidth)]));
                cairo_rectangle(c, x * pixelWidth, y * pixelHeight, pixelWidth, pixelHeight);
                cairo_fill(c);
            }
        }
    }
}
