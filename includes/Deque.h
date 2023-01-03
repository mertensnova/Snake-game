#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include "SDL2/SDL.h"

#include "Entity.h"
#include "Snake.h"


typedef struct Deque {
  
  Snake_Node *front;
  Snake_Node *rear;
  int length;

} Deque;

Deque* deque_init();

void deque_push(Deque *q, Vector *coords);
Vector *deque_front (Deque *q);
Vector *deque_back (Deque *q);
Vector *deque_pop(Deque *q);

void snake_movement( SDL_Renderer *renderer , Deque *snake, char *direction);
// void draw_snake( Deque *snake ,SDL_Renderer *renderer );
void draw_snake( Deque *snake ,SDL_Renderer *renderer ,char *direction);
void init_snake( Deque *snake ,SDL_Renderer *renderer );


#endif