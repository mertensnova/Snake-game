#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "includes/Entity.h"
#include "includes/Render.h"
#include "includes/Snake.h"



void snake_movement( SDL_Rect* rect,SDL_Renderer *renderer ,int up, int down, int left, int right, int score)
{
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, rect);


    SDL_RenderFillRect(renderer, rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


    SDL_Rect single_rect;
    SDL_Rect multi_rect[5];
    for (int i = 0; i < 5; i++)
    {
        single_rect.w = 50;
        single_rect.h = 50;
        single_rect.x = i * 50;
        single_rect.y = i * 50;
        SDL_SetRenderDrawColor(renderer, 255, (Uint8)(i * 50), 0, 255);
        SDL_RenderFillRect(renderer, &single_rect);

        multi_rect[i].w = 50;
        multi_rect[i].h = 50;
        multi_rect[i].x = i * 50 + 50;
        multi_rect[i].y = i * 50;
    }

    int velocity = 5;
    if (score >= 10)
    {
        velocity = 10;
    }

    if (score >= 20)
        velocity = 15;

    if (score >= 30)
        velocity = 20;

    if (score >= 40)
        velocity = 25;
        

    if (up && !down)
    {
        rect->w = 20;
        rect->h = 100;
        rect->y -=  (int) velocity;
        // printf("%d",rect->w);
    }
    
    if (down && !up)
    {
        rect->w = 20;
        rect->h = 100;
        rect->y +=  (int) velocity;
    }
    
    if (left && !right)
    {   
        rect->w = 100;
        rect->h = 20;
        rect->x -=  (int) velocity;
    }
    
    if (right && !left)
    {   
        rect->w = 100;
        rect->h = 20;
        rect->x +=  (int) velocity;
    }


    if (rect->x <= 0)
        rect->x =  SCREEN_WIDTH - rect->w;

    if (rect->x > SCREEN_WIDTH - rect->w )
        rect->x = 0;

    if (rect->y <= 0)
        rect->y =  SCREEN_HEIGHT - rect->h;

    if (rect->y > SCREEN_HEIGHT - rect->h )
        rect->y = 0;
  
    SDL_Delay(1000 / 60);

    SDL_RenderPresent( renderer );

}