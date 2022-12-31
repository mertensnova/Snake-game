#ifndef ENTITY_H
#define ENTITY_H
#include <stdbool.h>
#include "SDL2/SDL.h"


typedef struct Entity {
    float x,y;
    SDL_Texture* tex;
    SDL_Rect currentFrame;

} Entity;

typedef struct Vector {
  int x,y;
  
} Vector;

Vector *vector2f(float p_x, float p_y);
Entity *new_entity( Vector *pos, SDL_Texture *p_tex );
#endif