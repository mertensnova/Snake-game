#ifndef SNAKE_H
#define SNAKE_H
#include <stdbool.h>
#include "SDL2/SDL.h"

#include "Entity.h"

typedef struct Snake_Node {

    Vector body[192];
    int length;

} Snake_Node;


Vector *get_snake_head( Snake_Node *snake );
void render_snake( SDL_Renderer *renderer , Snake_Node *snake );
Vector peak_next_pos( Snake_Node *snake, char *direction );
void snake_movement( SDL_Renderer *renderer, Snake_Node *snake, char *direction );
#endif

