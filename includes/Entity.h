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
  float x,y;
} Vector;

Vector *position(float p_x, float p_y);
Entity *new_entity( Vector *pos, SDL_Texture *p_tex );
Entity *set_pos(SDL_Renderer *renderer, Entity *entity);
#endif