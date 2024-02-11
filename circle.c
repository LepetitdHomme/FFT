#include "includes/common.h"

// void drawCircle(SDL_Renderer* renderer, int x_center, int y_center, int radius, Uint32 time) {
//   int x = radius;
//   int y = 0;
//   int err = 0;

//   SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
//   /* Middle point circle algo */
//   while (x >= y) {
//     // printf("center: %d - %d | point: %d - %d | x: %d | y: %d\n", x_center, y_center, x_center + x, y_center + y, x, y);
//     SDL_RenderDrawPoint(renderer, x_center + y, y_center + x);// 0;1
//     SDL_RenderDrawPoint(renderer, x_center - y, y_center + x);// 0;1
//     SDL_RenderDrawPoint(renderer, x_center - x, y_center + y);// -1;0
//     SDL_RenderDrawPoint(renderer, x_center - x, y_center - y);// -1;0
//     SDL_RenderDrawPoint(renderer, x_center - y, y_center - x);// 0;-1
//     SDL_RenderDrawPoint(renderer, x_center + y, y_center - x);// 0;-1
//     SDL_RenderDrawPoint(renderer, x_center + x, y_center - y);// 1;0
//     if (err <= 0) {
//       y += 1;
//       err += 2*y + 1;
//     }
//     if (err > 0) {
//       x -= 1;
//       err -= 2*x + 1;
//     }
//   }
// }

coord_t       draw_radius(state_t *state, circle_t circle, int *ys, int last, int *counter) {
  coord_t coord;
  double angle;
  angle = 2 * M_PI * ((double)state->current_time / circle.period);

  coord.x = (int)(circle.radius * cos(-angle)) + circle.center.x;
  coord.y = (int)(circle.radius * sin(-angle)) + circle.center.y;

  if (last == 1) { // add y to array or ys
    ys[*counter] = coord.y;

    *counter += 1;
    if (*counter >= 1000) {
      *counter = 0;
    }

  }
  
  SDL_RenderDrawLine(state->renderer, circle.center.x, circle.center.y, coord.x, coord.y);
  return coord;
}

void          draw_middle_line(SDL_Renderer *renderer, coord_t coord) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  SDL_RenderDrawLine(renderer, coord.x, coord.y, WINDOW_WIDTH * 2 / 3, coord.y);
}
