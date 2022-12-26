#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "includes/Entity.h"
#include "includes/Render.h"
#include "includes/Snake.h"


void set_pos( Entity *snake)
{

    float y_pos = SCREEN_HEIGHT;
    float x_pos = SCREEN_WIDTH;
    float y_vel = SPEED;
    float x_vel = SPEED;

    if (snake->x <= 0)
    {
        snake->x = 0;
        x_vel = -x_vel;
    }
    if (snake->y <= 0)
    {
        snake->y = 0;
        y_vel = -y_vel;
    }
   if (x_pos >= SCREEN_WIDTH - snake->currentFrame.w )
    {
        x_pos = SCREEN_WIDTH - snake->currentFrame.w;
        x_vel = -x_vel;
    }
    if (y_pos >= SCREEN_HEIGHT - snake->currentFrame.h )
    {
        y_pos = SCREEN_HEIGHT - snake->currentFrame.h;
        y_vel = -y_vel;
    }

    snake->x += x_vel / 60;
    snake->y  += y_vel / 60;
    
    // snake->y =  y_pos;
    // snake->x =  x_pos;

    
    // SDL_Delay(1000/60);
}