#ifndef BALL_H
#define BALL_H
#include <stdbool.h>
#include "SDL2/SDL.h"

#include "Entity.h"


// One block of a snake body.
typedef struct Snake_Node {
    int x,y;
    struct Snake_Node* next;
    struct Snake_Node* prev;
} Snake_Node;

// void new();
void snake_movement( Entity *snake ,int up, int down, int left, int right, int score);

#endif

