#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>
#include <stdbool.h>

typedef struct Colour_ {
    uint8_t r, g, b;
} Colour;

Colour WHITE = {255, 255, 255};
Colour BLACK = {0, 0, 0};
Colour RED = {255, 0, 0};
Colour GREEN = {0, 255, 0};
Colour BLUE = {0, 0, 255};
Colour YELLOW = {255, 255, 0};
Colour PURPLE = {255, 0, 255};
Colour CYAN = {0, 255, 255};
Colour FAILED = {1,2,3};

bool equal_colours(Colour c1, Colour c2){
    if(c1.r==c2.r && c1.g==c2.g && c1.b==c2.b) return true;
    return false;
}


typedef struct Pixel_ {
    Colour colour;
} Pixel;


typedef struct Canvas_{
    int width, height;
    Pixel *pixels;
} Canvas;


Canvas *create_canvas(int width, int height){
    Canvas *c = malloc(sizeof(Canvas));
    c->width = width;
    c->height = height;
    c->pixels = calloc(width*height, sizeof(Pixel));
    return c;
}

void set_pixel(Canvas *c, size_t x, size_t y, Colour colour){
    //convert (x,y) coordinates of 2D canvas to flattened vector of pixel array
    //check if pixels are in canvas bounds and set Colour
    if(x>=0 && x<c->width && y>= 0 && y<c->height) c->pixels[y * c->width +x].colour = colour;
}

void save_canvas_as_png(Canvas *canvas, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to open file");
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, NULL);
        fclose(fp);
        return;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return;
    }

    png_set_compression_level(png, PNG_COMPRESSION_TYPE_DEFAULT);
    png_init_io(png, fp);
    png_set_IHDR(png, info, canvas->width, canvas->height, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_bytep *row_pointers = malloc(sizeof(png_bytep) * canvas->height);
    for (int y = 0; y < canvas->height; y++) {
        row_pointers[y] = (png_bytep)malloc(3 * canvas->width);
        for (int x = 0; x < canvas->width; x++) {
            Pixel p = canvas->pixels[y * canvas->width + x];
            row_pointers[y][x * 3] = p.colour.r;
            row_pointers[y][x * 3 + 1] = p.colour.g;
            row_pointers[y][x * 3 + 2] = p.colour.b;
        }
    }

    png_set_rows(png, info, row_pointers);
    png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);

    for (int y = 0; y < canvas->height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    png_destroy_write_struct(&png, &info);
    fclose(fp);
}




void free_canvas(Canvas *c){
    free(c->pixels);
    free(c);
}

bool pixel_on_canvas(Canvas *c, size_t x, size_t y){
    if(x>=0 && x<c->width && y>=0 && y<c->height) return true;
    return false;
}

Colour get_pixel_colour(Canvas *c, size_t x, size_t y){
    if(pixel_on_canvas(c, x, y)) return c->pixels[y * c->width + x].colour;
    return FAILED;
}
