#ifndef BALL_H
#define BALL_H
#include <stdbool.h>
#include "SDL2/SDL.h"

#include "Entity.h"

// void snake_movement( Entity *snake ,int up, int down, int left, int right, int score);
void snake_movement( SDL_Rect* rect,SDL_Renderer *renderer ,int up, int down, int left, int right, int score);
#endif




