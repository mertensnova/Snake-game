#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "includes/Entity.h"
#include "includes/Render.h"

Vector *position(float p_x, float p_y)
{
     Vector *vec = malloc(sizeof(Vector));

     vec->y = p_y;
     vec->x = p_x;
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
    entity->currentFrame.w  = 32;
    entity->currentFrame.h  = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &entity->currentFrame.w, &entity->currentFrame.h);

    return entity;
}


Entity *set_pos(SDL_Renderer *renderer, Entity *entity)
{
    SDL_Rect dest;
    float y_pos = SCREEN_HEIGHT;
    float x_pos = SCREEN_WIDTH;

    SDL_QueryTexture(entity->tex,NULL,NULL,&dest.w,&dest.h);

    while (dest.y >=  -dest.h)
    {
        // SDL_RenderClear( renderer );  
        entity->y = (int) y_pos;
        

        // SDL_RenderCopy( renderer, entity->tex, NULL, &dest );
        // SDL_RenderPresent( renderer );
        y_pos -= (float) SPEED / 60;

        SDL_Delay(1000/60);
    }

    return entity;
}

