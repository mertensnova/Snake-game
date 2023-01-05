#ifndef RENDER_H
#define RENDER_H
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "Entity.h"

//Screen dimension constants
#define SCREEN_WIDTH (600)
#define SCREEN_HEIGHT (480)
#define SPEED  (300)
#define MAX_SNAKE_LENGTH ((SCREEN_WIDTH) * (SCREEN_HEIGHT))

void game(void);
bool init(void);
#endif