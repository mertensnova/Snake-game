#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Entity.h"
#include "Render.h"
#include "Snake.h"
#include "Deque.h"

void init_snake( Deque *snake ,SDL_Renderer *renderer )
{
    for (int i = 0; i < 5; i++)
	{
        Vector position = { SCREEN_WIDTH / 2 - i , SCREEN_HEIGHT / 2 };
		deque_push( snake, &position );
	}
}


void draw_snake( Deque *snake ,SDL_Renderer *renderer )
{

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_Rect rect[10];

    for (int i = 0; i < 10; i++)
	{
        Snake_Node* tmp = snake->front;
        while (tmp != NULL)
	    {
            rect[i].x = i * tmp->coords->x / 20;
            rect[i].y = tmp->coords->y;
		    tmp = tmp->next;
	    }

        rect[i].h = 20;
        rect[i].w = 20;
    }

    int head = rect[0].x;


    SDL_RenderDrawRects(renderer, rect,10);
    SDL_RenderFillRects(renderer, rect,10);
}

void snake_movement( SDL_Renderer *renderer , Deque *snake  ,int up, int down, int left, int right)
{

    Vector *snake_head = deque_front(snake);
    if (down && !up)
       snake_head->y+= 1;

    if (!down && up)
       snake_head->y -= 1;

    if (left && !right)
       snake_head->x -= 10;

    if (right && !left)
       snake_head->x += 10;
    
    //  if (snake_head->x <= 0)
    //     snake_head->x =  SCREEN_WIDTH - snake->length;

    // if (snake_head->x> SCREEN_WIDTH - snake->length )
    //     snake_head->x = 0;

    // if (snake_head->y <= 0)
    //     snake_head->y =  SCREEN_HEIGHT - snake->length;

    // if (snake_head->y > SCREEN_HEIGHT - snake->length )
    //     snake_head->y = 0;

    
    
    deque_push(snake, snake_head);
    // deque_pop(snake);
    // SDL_RenderClear(renderer);
    draw_snake( snake, renderer );
    SDL_Delay(1000/60);
}

