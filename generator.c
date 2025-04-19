#include "draw_utils.c"
#include <asm-generic/errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

Canvas* generate(int width, int height, int num_v_lines, int num_h_lines, int num_discontinued_v_lines, int num_discontinued_h_lines,
                 int min_distance_between_lines, int num_red, int num_blue, int num_yellow, int num_black){
    Canvas *c = create_canvas(width, height);
    // White canvas
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            set_pixel(c, i, j, WHITE);
        }
    }
    //Array of h line positions
    int total_h_lines = num_h_lines+num_discontinued_h_lines+2;//add 2 for top and bottom
    int h_line_positions[total_h_lines];
    h_line_positions[total_h_lines-1] = 0;
    h_line_positions[total_h_lines-2] = height;
    int num_h_lines_drawn = 0;

    //Array of v line positions
    int total_v_lines = num_v_lines+num_discontinued_v_lines+2;//add 2 for left and right
    int v_line_positions[total_v_lines];
    v_line_positions[total_v_lines-1] = 0;
    v_line_positions[total_v_lines-2] = width;
    int num_v_lines_drawn = 0;
 
    srand(time(0)); //seed rng
                    
    //drawing lines
    for(int i=0; i<num_v_lines; i++){
        bool too_close = false;
        //random number between 0 and width
        int x = rand() % width+1;



        for(int j=0; j<total_v_lines; j++){
            if(abs(v_line_positions[j]-x)<min_distance_between_lines){
                too_close = true;
            }        
        }
        if(too_close) continue;
        v_line_positions[num_v_lines_drawn] = x;
        num_v_lines_drawn++;
        draw_vertical_line(c, x, 10, BLACK);
    }
    
    for(int i=0; i<num_h_lines; i++){
        bool too_close = false;
        //random number between 0 and width
        int y = rand() % height+1;

        for(int j=0; j<total_h_lines; j++){
            if(abs(h_line_positions[j]-y)<min_distance_between_lines){
                too_close = true;
            }        
        }
        if(too_close) continue;
        h_line_positions[num_h_lines_drawn] = y;
        num_h_lines_drawn++;
        draw_horizontal_line(c, y, 10, BLACK);
    }

    //draw discontinued lines
    for(int i=0; i<num_discontinued_h_lines; i++){
        bool too_close = false;
        int y = rand() % width+1;
        int k = rand() % num_v_lines;
        int n = rand() % num_v_lines+1;
        if(k>n){
            int tmp = k;
            int k = n;
            int n = tmp;
        }
        if(k==n) n++;
        for(int j=0; j<total_h_lines; j++){
            if(abs(h_line_positions[j]-y)<min_distance_between_lines){
                too_close = true;
            }        
        }
        if(too_close) continue;
        h_line_positions[num_h_lines_drawn] = y;
        num_h_lines_drawn++;
        draw_horizontal_line_from_kth_to_nth_intersection(c, k, n, y, 10, BLACK);
    }


    for(int i=0; i<num_discontinued_v_lines; i++){
        bool too_close = false;
        int x = rand() % height+1;
        int k = rand() % num_h_lines;
        int n = rand() % num_h_lines+1;
        if(k>n){
            int tmp = k;
            int k = n;
            int n = tmp;
        }
        if(k==n) n++;
        for(int j=0; j<total_v_lines; j++){
            if(abs(v_line_positions[j]-x)<min_distance_between_lines){
                too_close = true;
            }        
        }
        if(too_close) continue;
        v_line_positions[num_v_lines_drawn] = x;
        num_v_lines_drawn++;
        draw_vertical_line_from_kth_to_nth_intersection(c, k, n, x, 10, BLACK);
    }

    //drawing coloured areas
    for(int i=0; i<num_black; i++){
        int x = rand() % width+1;
        int y = rand() % height+1;

        while(equal_colours(get_pixel_colour(c, x, y), BLACK)){
            x = rand() % width+1;
            y = rand() % height+1;
        } 
        if(equal_colours(get_pixel_colour(c, x, y), WHITE)){
            fill_rectangle_area_from_pixel(c, x, y, BLACK);
        }
    }
    for(int i=0; i<num_yellow; i++){


        int x = rand() % width+1;
        int y = rand() % height+1;

        while(equal_colours(get_pixel_colour(c, x, y), BLACK)){
            x = rand() % width+1;
            y = rand() % height+1;
        }
        if(equal_colours(get_pixel_colour(c, x, y), WHITE)){
            fill_rectangle_area_from_pixel(c, x, y, YELLOW);
        }
    }
    for(int i=0; i<num_blue; i++){
        int x = rand() % width+1;
        int y = rand() % height+1;

        while(equal_colours(get_pixel_colour(c, x, y), BLACK)){
            x = rand() % width+1;
            y = rand() % height+1;
        } 
        if(equal_colours(get_pixel_colour(c, x, y), WHITE)){
            fill_rectangle_area_from_pixel(c, x, y, BLUE);
        }
    }

    for(int i=0; i<num_red; i++){
        int x = rand() % width+1;
        int y = rand() % height+1;

        while(equal_colours(get_pixel_colour(c, x, y), BLACK)){
            x = rand() % width+1;
            y = rand() % height+1;
        }
        if(equal_colours(get_pixel_colour(c, x, y), WHITE)){
            fill_rectangle_area_from_pixel(c, x, y, RED);
        }
    }
        
    


    return c;
}
Canvas* generate_symmetric(){
    int width = 151;
    int height = 100;
    Canvas *c = create_canvas(width, height);
    // White canvas
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            set_pixel(c, i, j, WHITE);
        }
    }
    draw_symetric_vertical_line(c, 1, 1, 10, BLACK);
    return c;

}

int main(){
    Canvas *c = generate_symmetric();
    save_canvas_as_png(c, "output.png");
    free_canvas(c);

}

void saver(){
    srand(time(0)); //seed rng
                    
    int width = 500;
    int height = 500;
    int strokesize = 10; // TODO implement in generate() function
    int num_v_lines = 3;
    int num_h_lines = 3;
    int num_discontinued_v_lines = 5;
    int num_discontinued_h_lines = 5;
    int num_red = 2;
    int num_blue = 2;
    int num_yellow = 2;
    int num_black = 1;
    int min_distance_between_lines = 3 * strokesize;
    Canvas *c = generate(width, height, num_v_lines, num_h_lines, num_discontinued_v_lines, num_discontinued_h_lines, min_distance_between_lines, num_red, num_blue, 
                         num_yellow, num_black);

   
}

