#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "includes/Entity.h"


Entity *new_entity( float p_x, float p_y, SDL_Texture *p_tex )
{
    Entity *entity = malloc(sizeof(Entity));
    float x,y;
    x = p_x;
    y = p_y;

    entity->currentFrame.x  = 0;
    entity->currentFrame.y  = 0;
    entity->currentFrame.w  = 32;
    entity->currentFrame.h  = 32;
    
    return entity;
}