#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "includes/Entity.h"
#include "includes/Render.h"




void set_pos(Entity *ball)
{
    SDL_Rect dest;
    
    // dest.x = (SCREEN_WIDTH -dest.w) / 2;

    // float x_vel = SPEED;
    // float y_vel = SPEED;
    // float x_pos =  (SCREEN_WIDTH - dest.w) / 2;
    // float y_pos =  (SCREEN_HEIGHT - dest.h) / 2;
    dest.y += 20; 
    dest.x += 20;

    ball->x = dest.x;
    ball->y = dest.y;
    SDL_QueryTexture(ball->tex,NULL,NULL,&dest.w,&dest.h);
    // SDL_RenderCopy()
}