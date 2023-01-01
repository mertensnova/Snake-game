#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Entity.h"
#include "Render.h"
#include "Snake.h"
#include "Deque.h"



void draw_snake( Deque *snake ,SDL_Renderer *renderer, int up, int down, int left, int right )
{

    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_Rect rect[10];

    for (int i = 0; i < 10; i++)
	{
		Vector position = { SCREEN_WIDTH / 2 - i , SCREEN_HEIGHT / 2 };
		deque_push( snake, &position );
        Snake_Node* tmp = snake->front;

        while (tmp != NULL)
	    {
            rect[i].x = i * tmp->coords->x / 15;
            rect[i].y = tmp->coords->y;
		    tmp = tmp->next;
	    }

        rect[i].h = 20;
        rect[i].w = 20;
	}

    SDL_RenderDrawRects(renderer, rect, 10);

    SDL_RenderFillRects(renderer, rect , 10);

    SDL_RenderPresent(renderer);

}


void snake_movement( SDL_Renderer *renderer ,Deque *snake  ,int up, int down, int left, int right)
{
    Vector *snake_head = deque_back(snake);
    Vector *next_direction;

    if (up && !down)
    {
       snake_head->y += - SPEED / 60;
       printf("%d\n", snake_head->y);
    }

    
    // deque_push( snake, snake_head );
    draw_snake( snake_head , renderer , up,  down, left, right );
    // draw_snake(snake_head, up,  down, left, right );

    // if (down && !up)
    // {
    // //    snake_head->x += 0;
    //    snake_head->y += 1;
    // }

    // if (left && !right)
    // {
    //    snake_head->x += 1;
    // //    snake_head->y += 0;
    // }

    // if (right && !left)
    // {
    //    snake_head->x -= 1;
    // //    snake_head->y += 0;
    // }

}
