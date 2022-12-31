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

    snake_movement( snake, up,  down, left, right);

    SDL_RenderDrawRects(renderer, rect, 10);

    SDL_RenderFillRects(renderer, rect , 10);

    SDL_RenderPresent(renderer);

}


void snake_movement( Deque *snake  ,int up, int down, int left, int right)
{
    Vector *snake_head = deque_back(snake);
    Vector *next_direction;

    if (up && !down)
    {
       next_direction->x += 0;
       next_direction->y += -1;
    }


    if (down && !up)
    {
       next_direction->x += 0;
       next_direction->y += 1;
    }

    if (left && !right)
    {
       next_direction->x += 1;
       next_direction->y += 0;
    }

    if (right && !left)
    {
       next_direction->x -= 1;
       next_direction->y += 0;
    }

	// Vector next_direction = directions[0];
	Vector *snake_new_head = {snake_head->x + next_direction->x, snake_head->y + next_direction->y};
    deque_push( snake, snake_new_head );


    // int velocity = SPEED / 60;

    // if (snake->x <= 0)
    //     snake->x =  SCREEN_WIDTH - snake->currentFrame.w;

    // if (snake->x> SCREEN_WIDTH - snake->currentFrame.w )
    //     snake->x = 0;

    // if (snake->y <= 0)
    //     snake->y =  SCREEN_HEIGHT - snake->currentFrame.h;

    // if (snake->y > SCREEN_HEIGHT - snake->currentFrame.h )
    //     snake->y = 0;


    // SDL_Delay(1000 / 30);
}
