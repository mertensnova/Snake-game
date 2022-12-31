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





#endif