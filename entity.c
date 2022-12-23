#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "includes/Entity.h"



Vector *position(float p_x, float p_y,float p_w, float p_h)
{
     Vector *vec = malloc(sizeof(Vector));  
     vec->x = p_x;
     vec->y = p_y;
     vec->w = p_w;
     vec->h = p_h;
     return vec;
}

Entity *new_entity( Vector *pos, SDL_Texture *p_tex )
{
    Entity *entity = malloc(sizeof(Entity));
   
    entity->x = pos->x;
    entity->y = pos->y;
    entity->tex = p_tex;

    entity->currentFrame.x  = 0;
    entity->currentFrame.y  = 0;
    entity->currentFrame.w  = pos->w;
    entity->currentFrame.h  = pos->h;
    SDL_QueryTexture(p_tex, NULL, NULL, &entity->currentFrame.w, &entity->currentFrame.h);

    return entity;
}