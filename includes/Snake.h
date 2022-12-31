#ifndef SNAKE_H
#define SNAKE_H
#include <stdbool.h>
#include "SDL2/SDL.h"

#include "Entity.h"


// One block of a snake body.

typedef struct Snake_Node {

    Vector *coords;
    struct Snake_Node *next;

} Snake_Node;


void snake_movement( Entity *snake ,int up, int down, int left, int right, int score);
void draw_snake( SDL_Renderer *renderer ,int up, int down, int left, int right );
#endif

