#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
	SDL_Renderer *renderer;
	SDL_Event 		event;
	int 					quit;
	Uint32 				current_time;
} state_t;

typedef struct {
	int 				x;
	int 				y;
} coord_t;

typedef struct {
	coord_t 	center;
	int 			radius;
	double 		period;
} circle_t;

coord_t 			draw_radius(state_t *state, circle_t circle, int *ys, int last, int *counter);
void 					draw_middle_line(SDL_Renderer *renderer, coord_t coord);

#endif