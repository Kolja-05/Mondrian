#include "canvas.c"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


void draw_horizontal_line(Canvas *c, size_t y, size_t strokesize, Colour colour){
    for(int x=0; x<c->width; x++){
        for(int k=0; k<strokesize; k++){
            set_pixel(c, x, y+k, colour);
        }
    }
}

void draw_vertical_line(Canvas *c, size_t x, size_t strokesize, Colour colour){
    for(int y=0; y<c->height; y++){
        for(int k=0; k<strokesize; k++){
            set_pixel(c, x+k, y, colour);
        }
    }
}

void draw_rectangle(Canvas *c, int start_x, int start_y, int width, int height, Colour colour){
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            if(start_x+x>=0 && start_x+x<c->width && start_y+y>=0 && start_y+y<c->height){
                set_pixel(c, start_x + x, start_y + y, colour);
            }
        }
    }
}


//Helperfunction
void draw_vertical_line_between_pionts(Canvas *c, size_t x, size_t y1, size_t y2, size_t strokesize, Colour colour){
    for(int y=y1; y<y2; y++){
        for(int k=0; k< strokesize; k++){
            set_pixel(c, x+k, y, colour);
        }    
    }
}


//an intersection is only counted if the colour is the colour of the line you want to draw
void draw_vertical_line_from_kth_to_nth_intersection(Canvas *c, size_t k, size_t n, size_t x, size_t strokesize, Colour colour){
    if (k>n) return;
    int start_y = -1;
    for(int y=0; y<c->width; x+y++){
        if(k==0){
            start_y = 0;
            break; //start from the canvas edge if k=0
        }
        if(equal_colours(get_pixel_colour(c, x, y), colour)){
            k--;
            if(k==0){
                start_y = y;
                break;
            }

            //skip to next pixel where pixel colour != line colour 
            while(equal_colours(get_pixel_colour(c, x, y), colour)) y++;
        }
    }
                       
    int end_y = start_y;
    for(int y=0; y<c->width; y++){
        if(equal_colours(get_pixel_colour(c, x, y), colour)){
            n--;
            if(n==0){
                end_y = y;
                break;
            }

            //skip to next pixel where pixel colour != line colour 
            while(equal_colours(get_pixel_colour(c, x, y), colour)) y++;
        }
    }

    draw_vertical_line_between_pionts(c, x, start_y, end_y, strokesize, colour);
}





//Helperfunction
void draw_horizontal_line_between_pionts(Canvas *c, size_t y, size_t x1, size_t x2, size_t strokesize, Colour colour){
    for(int x=x1; x<x2; x++){
        for(int k=0; k< strokesize; k++){
            set_pixel(c, x, y+k, colour);
        }    
    }
}


//an intersection is only counted if the colour is the colour of the line you want to draw
void draw_horizontal_line_from_kth_to_nth_intersection(Canvas *c, size_t k, size_t n, size_t y, size_t strokesize, Colour colour){
    if (k>n) return;
    int start_x = -1;
    for(int x=0; x<c->width; x++){
        if(k==0){
            start_x = 0;
            break; //start from the canvas edge if k=0
        }
        if(equal_colours(get_pixel_colour(c, x, y), colour)){
            k--;
            if(k==0){
                start_x = x;
                break;
            }

            //skip to next pixel where pixel colour != line colour 
            while(equal_colours(get_pixel_colour(c, x, y), colour)) x++;
        }
    }
                       
    int end_x = start_x;
    //while(equal_colours(get_pixel_colour(c, end_x, y), colour)) end_x++; //TODO dont know if needed
    for(int x=0; x<c->width; x++){
        if(equal_colours(get_pixel_colour(c, x, y), colour)){
            n--;
            if(n==0){
                end_x = x;
                break;
            }

            //skip to next pixel where pixel colour != line colour 
            while(equal_colours(get_pixel_colour(c, x, y), colour)) x++;
        }
    }

    draw_horizontal_line_between_pionts(c, y, start_x, end_x, strokesize,colour);
}




void fill_rectangle_area_from_pixel(Canvas *c, int x, int y, Colour colour){
        
    Colour start_colour = get_pixel_colour(c, x, y);
    int pos1_x = x;
    int pos1_y = y;
    int pos2_x = x;
    int pos2_y = y;
    if(x>=0 && x<c->width && y>=0 && y<c->width){
        //find top left corner of the rectangle area
        // find x
        while(pos1_x>=0 && pos1_x<c->width && equal_colours(get_pixel_colour(c, pos1_x-1, pos1_y), start_colour)){
            pos1_x--;
        }

        //find y
        while(pos1_y>=0 && pos1_y<c->height && equal_colours(get_pixel_colour(c, pos1_x, pos1_y-1), start_colour)){
            pos1_y--;
        }
        // find bottom right corner
        // find x
        while(pos2_x>=0 && pos2_x<c->width && equal_colours(get_pixel_colour(c, pos2_x+1, pos2_y), start_colour)){
            pos2_x++;
        }
        // find y
        while(pos2_y>=0 && pos2_y<c->height && equal_colours(get_pixel_colour(c, pos2_x, pos2_y+1), start_colour)){
            pos2_y++;
        }

        pos2_x++;
        pos2_y++;

        //calculate width and height for rectangle

        size_t width = pos2_x - pos1_x;
        size_t height = pos2_y - pos1_y;
        
        //draw rectangle
       
        draw_rectangle(c,pos1_x, pos1_y, width, height, colour);
    }
    
}

//from origin finde next lines to the left and right (or canvas bound) and draw a line in the middle, so that it splits the area in two symmetric ones
void draw_symetric_vertical_line(Canvas *c, int origin_x, int y, int strokesize, Colour colour){
    int left = origin_x;
    int right = origin_x;
    printf("pixel origin x y: %d, %d \n", origin_x, y);
    printf("pixel on canvas: %d \n", pixel_on_canvas(c, origin_x, y));
    if(!pixel_on_canvas(c, origin_x, y)) return;
    printf("reached 1 \n");
    //find left
    while(pixel_on_canvas(c, left-1, y)){
        left--;
    }
    printf("reached 2\n");
    //find right
    while(pixel_on_canvas(c, right+1, y)){
        right++;
    }

    printf("reached 3\n");
    //calculate middle while avoiding overflow
    int mid = left + (right - left) / 2;
    printf("%d", mid);

    //paint upward from (mid, y)
    int step = 0;
    while (pixel_on_canvas(c, mid, y+step)){
        if(equal_colours(get_pixel_colour(c, mid, y+step), BLACK)) break;
        for(int i=0; i<strokesize/2; i++){
            set_pixel(c, mid+i, y+step, colour);
            set_pixel(c, mid-i, y+step, colour);
        }
        step++;
    }
    //paint downward from (mid, y)
    step = 1;//0 has already been painted
    while (pixel_on_canvas(c, mid, y-step)){
        if(equal_colours(get_pixel_colour(c, mid, y-step), BLACK)) break;
        
        for(int i=0; i<strokesize/2; i++){
            set_pixel(c, mid+i, y-step, colour);
            set_pixel(c, mid-i, y-step, colour);
        }
        step++;
    }
    
    printf("step: %d \n", step);
}






