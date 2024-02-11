#include "includes/common.h"

int random_int() {
  int r = rand() % 50;
  return (r + 10);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  state_t state;

  printf("Starting SDL2 application\n");
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL initialization failed: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Fourier playfround", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window creation failed: %s\n", SDL_GetError());
    return 1;
  }

  state.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  state.quit = 0;
  state.current_time = SDL_GetTicks();


  coord_t coord;
  int ys[1000] = { 0 };
  int counter = 0;
  coord_t center;
  center.x = 200;
  center.y = 300;
  circle_t circle;
  circle.center = center;
  circle.radius = 60;
  circle.period = 4000.0;

  while (!state.quit) {

    if (state.current_time != 0) {
      state.current_time = SDL_GetTicks();
    }

    while (SDL_PollEvent(&state.event)) {
      if (state.event.type == SDL_QUIT) {
        state.quit = 1;
      }
    }

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
    coord = draw_radius(&state, circle, ys, 1, &counter);
    // coord = draw_radius(&state, coord.x, coord.y, 30, 2000.0, state.current_time, ys, 0, &counter);
    // coord = draw_radius(&state, coord.x, coord.y, 20, 1000.0, state.current_time, ys, 1, &counter);

    draw_middle_line(state.renderer, coord);

    SDL_SetRenderDrawColor(state.renderer, 0, 255, 0, 255);

    int x = 0;
    for (int i = counter ; i >= 0 ; i--) {
      SDL_RenderDrawPoint(state.renderer, WINDOW_WIDTH * 2 / 3 + (x / 5), ys[i]);
      x++;
    }
    for (int i = 999; i > counter; i--) {
      SDL_RenderDrawPoint(state.renderer, WINDOW_WIDTH * 2 / 3 + (x / 5), ys[i]);
      x++;      
    }
    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(state.renderer, 200, 300, WINDOW_WIDTH, 300);


    SDL_RenderPresent(state.renderer);
    // COmment/Uncomment to limit frame rate (approximately 60 FPS) 
    SDL_Delay(8);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
