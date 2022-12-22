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

Entity *new_entity( float p_x, float p_y, SDL_Texture *p_tex );
#endif