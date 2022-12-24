#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "includes/Entity.h"

Vector *position(float p_x, float p_y)
{
     Vector *vec = malloc(sizeof(Vector));
    //   SDL_Event event;
    //     while ( SDL_PollEvent( &event ) )
    //     {
    //          if( event.type == SDL_KEYDOWN )
    //         {
    //             //Select surfaces based on key press
    //             switch( event.key.keysym.sym )
    //             {
    //             case SDLK_UP:
    //                vec->x = p_x + 10 ;
    //                printf("HELLO WORLD")
    //             break;

    //             case SDLK_DOWN:
    //                 vec->y = p_y - 10;
    //             break;
    //             default:
    //             vec->y = p_y;
    //             break;
        //         }
        //     }  
        // }
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
