#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

void draw_snake( Deque *snake ,SDL_Renderer *renderer ,char *direction)
{

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_Rect rect[10];

    for (int i = 0; i < 5; i++)
    {   
        
        Snake_Node* tmp = snake->front;
        while (tmp != NULL)
	    {
            rect[0].x = tmp->coords->x;
            rect[0].y = tmp->coords->y;
		    tmp = tmp->next;
	    }
        rect[i].h = 20;
        rect[i].w = 20;
        rect[i].x = rect[0].x - 30 * i; 
        rect[i].y = rect[0].y; 
    }



    SDL_RenderDrawRects(renderer, rect,5);
    SDL_RenderFillRects(renderer, rect,5);
}

void snake_movement( SDL_Renderer *renderer , Deque *snake, char *direction)
{

    Vector *snake_head = deque_front(snake);
    Vector new_head;

    if (!strcmp(direction, "down"))
       snake_head->y += 1; 

    if (!strcmp(direction, "up"))
        snake_head->y -= 1;

    if (!strcmp(direction, "left"))
       snake_head->x -= 10;

    if (!strcmp(direction, "right"))
      snake_head->x += 10;

    new_head.x = snake_head->x;
    new_head.y = snake_head->y;
  

   draw_snake( snake, renderer ,direction);
   deque_push( snake, &new_head);
   SDL_Delay(1000/60);
}

