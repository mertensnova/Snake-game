#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "includes/Entity.h"
#include "includes/Render.h"
#include "includes/Snake.h"
#include "includes/Deque.h"



// void PrintSnake (Deque *snake)
// {
// 	Snake_Node* tmp = snake->front;
// 	while (tmp != NULL)
// 	{
// 		GoToPosition(tmp->coords);
// 		printf("%c", SnakeElement);
// 		tmp = tmp->next;
// 	}
// }

void draw_snake( SDL_Renderer *renderer ,int up, int down, int left, int right )
{

    Deque *snake = deque_init();

    Snake_Node* tmp = snake->front;
    SDL_RenderClear( renderer );  

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_Rect rect[10];

    for (int i = 0; i < 10; i++)
	{
		Vector position = { SCREEN_WIDTH / 2 - i , SCREEN_HEIGHT / 2 };
		deque_push( snake, &position );
        while (tmp != NULL)
	    {
		// GoToPosition(tmp->coords);
        rect[i].x = tmp->coords->x;
        rect[i].y = tmp->coords->y;
		tmp = tmp->next;
        
	    }

        rect[i].w  = 20;
        rect[i].h = 20;

	}

    SDL_RenderDrawRects(renderer, rect, 10);

    SDL_RenderFillRects(renderer, rect , 10);
    
    SDL_RenderPresent(renderer);

}


void snake_movement( Entity *snake ,int up, int down, int left, int right, int score)
{

    int velocity = SPEED / 60;

    if (up && !down)
        snake->y -=  velocity;
    
    if (down && !up)
        snake->y += (int) velocity;
    
    if (left && !right)
        snake->x -=  (int) velocity;
    
    if (right && !left)
        snake->x +=  (int) velocity;

    if (snake->x <= 0)
        snake->x =  SCREEN_WIDTH - snake->currentFrame.w;

    if (snake->x> SCREEN_WIDTH - snake->currentFrame.w )
        snake->x = 0;

    if (snake->y <= 0)
        snake->y =  SCREEN_HEIGHT - snake->currentFrame.h;

    if (snake->y > SCREEN_HEIGHT - snake->currentFrame.h )
        snake->y = 0;
  

    SDL_Delay(1000 / 30);
}
