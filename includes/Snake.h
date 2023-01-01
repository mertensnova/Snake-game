#ifndef SNAKE_H
#define SNAKE_H
#include <stdbool.h>
#include "SDL2/SDL.h"

#include "Entity.h"

typedef struct Snake_Node {

    Vector *coords;
    struct Snake_Node *next;

} Snake_Node;

#endif

