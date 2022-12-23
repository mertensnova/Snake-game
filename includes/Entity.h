#ifndef ENTITY_H
#define ENTITY_H
#include <stdbool.h>
#include "SDL2/SDL.h"


typedef struct
{
    float x,y;
    SDL_Texture* tex;
    SDL_Rect currentFrame;

} Entity;

typedef struct 
{
  float x,y,w,h;
} Vector;

Vector *position(float p_x, float p_y,float p_w, float p_h);
Entity *new_entity( Vector *pos, SDL_Texture *p_tex );
#endif