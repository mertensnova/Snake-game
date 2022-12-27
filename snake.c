#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "includes/Entity.h"
#include "includes/Render.h"
#include "includes/Snake.h"


void snake_movement( Entity *snake ,int up, int down, int left, int right)
{

    if (up && !down)
        snake->y -=  (int) 1;
    
    if (down && !up)
        snake->y +=  (int) 1;
    
    if (left && !right)
        snake->x -=  (int) 1;
    
    if (right && !left)
        snake->x +=  (int) 1;


    if (snake->x <= 0)
        snake->x =  SCREEN_WIDTH - snake->currentFrame.w;

    if (snake->x > SCREEN_WIDTH - snake->currentFrame.w )
        snake->x = 0;

    if (snake->y <= 0)
        snake->y =  SCREEN_HEIGHT - snake->currentFrame.h;

    if (snake->y > SCREEN_HEIGHT - snake->currentFrame.h )
        snake->y = 0;
  
    SDL_Delay(1000 / 90);
}