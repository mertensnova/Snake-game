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
    SDL_Rect rect;
    Snake_Node* tmp = snake->front;
        while (tmp != NULL)
	    {
            rect.x =  tmp->coords->x / 20;
            rect.y = tmp->coords->y;
		    tmp = tmp->next;
	    }

    rect.h = 20;
    rect.w = 20;
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}

void snake_movement( SDL_Renderer *renderer , Deque *snake  ,int up, int down, int left, int right)
{

    static const int moveX[] = { 0, 0, -10, 10 };
    static const int moveY[] = { -10, 10, 0, 0 };

    Vector *snake_head = deque_front(snake);
    unsigned y;
    unsigned x;

    if (down && !up)
    {
       snake_head->y += 1; 
    }

    if (!down && up)
    {
     snake_head->y -= 1;
    }

    if (left && !right)
    {
       snake_head->x -=50;
    }

    if (right && !left)
    {
      snake_head->x +=50;
    }

    Vector new_head;
    new_head.x = snake_head->x - 20;
    new_head.y = snake_head->y - 20;
  
   draw_snake( snake, renderer );
   deque_push( snake, snake_head);
   draw_snake( snake, renderer );
   deque_push( snake, &new_head);
   SDL_Delay(1000/60);
}

