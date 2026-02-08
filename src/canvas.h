#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>





typedef struct Colour_ {
    int16_t r, g, b;
} Colour;

#define WHITE  ((Colour){255, 255, 255})
#define BLACK  ((Colour){0, 0, 0})
#define RED  ((Colour){255, 0, 0})
#define GREEN  ((Colour){0, 255, 0})
#define BLUE  ((Colour){0, 0, 255})
#define YELLOW  ((Colour){255, 255, 0})
#define PURPLE  ((Colour){255, 0, 255})
#define CYAN  ((Colour){0, 255, 255})
#define FAILED  ((Colour){-1,-1,-1})





typedef struct Pixel_ {
    Colour colour;
} Pixel;


typedef struct Canvas_{
    int width, height;
    Pixel *pixels;
} Canvas;


bool equal_colours(Colour c1, Colour c2);


Canvas *create_canvas(int width, int height);

void set_pixel(Canvas *c, size_t x, size_t y, Colour colour);

void save_canvas_as_png(Canvas *canvas, const char *filename);



void free_canvas(Canvas *c);

bool pixel_on_canvas(Canvas *c, size_t x, size_t y);


Colour get_pixel_colour(Canvas *c, size_t x, size_t y);

#endif
