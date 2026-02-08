#ifndef DRAW_UTILS_H
#define DRAW_UTILS_H


#include "canvas.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



void draw_horizontal_line(Canvas *c, size_t y, size_t strokesize, Colour colour);

void draw_vertical_line(Canvas *c, size_t x, size_t strokesize, Colour colour);

void draw_rectangle(Canvas *c, int start_x, int start_y, int width, int height, Colour colour);

//Helperfunction
void draw_vertical_line_between_pionts(Canvas *c, size_t x, size_t y1, size_t y2, size_t strokesize, Colour colour);

//an intersection is only counted if the colour is the colour of the line you want to draw
void draw_vertical_line_from_kth_to_nth_intersection(Canvas *c, size_t k, size_t n, size_t x, size_t strokesize, Colour colour);




//Helperfunction
void draw_horizontal_line_between_pionts(Canvas *c, size_t y, size_t x1, size_t x2, size_t strokesize, Colour colour);


//an intersection is only counted if the colour is the colour of the line you want to draw
void draw_horizontal_line_from_kth_to_nth_intersection(Canvas *c, size_t k, size_t n, size_t y, size_t strokesize, Colour colour);



void fill_rectangle_area_from_pixel(Canvas *c, int x, int y, Colour colour);

//from origin finde next lines to the left and right (or canvas bound) and draw a line in the middle, so that it splits the area in two symmetric ones
void draw_symetric_vertical_line(Canvas *c, int origin_x, int y, int strokesize, int min_distance_between_lines, Colour colour);

#endif // !DRAW_UTILS_H

