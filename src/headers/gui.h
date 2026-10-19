#ifndef DRAW_H
#define DRAW_H

#include <stdbool.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include "collections.h"
#include "utils.h"

#define PIXEL_WIDTH 1
#define PIXEL_HEIGHT 1
#define IMAGE_INIT_WIDTH 750
#define IMAGE_INIT_HEIGHT 500
#define WINDOW_TITLE "RAY-TRACING"

#define FOV 90
#define TRANSLATE_X 0
#define TRANSLATE_Y -2
#define TRANSLATE_Z -3
#define ROTATE_X -30
#define ROTATE_Y -50
#define ROTATE_Z 0

void draw(GtkWidget *widget, cairo_t *c, gpointer userData);
void activate(GtkApplication *app, gpointer userData);

typedef struct image {
    int imageWidth;
    int imageHeight;
    double *buffer;
    bool render;
} image, *Image;

bool load(char *filename);
double *render(int imageWidth, int imageHeight);
int bufferIndex(int x, int y, int imageWidth);

#endif
