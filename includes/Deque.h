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
void draw_snake( Deque *snake ,SDL_Renderer *renderer, int up, int down, int left, int right );
void snake_movement( Deque *snake  ,int up, int down, int left, int right);





#endif