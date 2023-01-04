#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Entity.h"
#include "Render.h"
#include "Snake.h"


Vector *get_snake_head(Snake_Node *snake) 
{
  return &snake->body[snake->length - 1];
}



void render_snake( SDL_Renderer *renderer , Snake_Node *snake )
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    for (int i = snake->length - 1; i >= 0; --i)
    {

      SDL_Rect rect;
      rect.x = snake->body[i].x; 
      rect.y = snake->body[i].y;
      rect.h = 20;
      rect.w = 20;

      SDL_RenderDrawRect(renderer, &rect);
      SDL_RenderFillRect(renderer, &rect);
    }
  

}
Vector peak_next_pos(Snake_Node *snake, char *direction) 
{
    Vector new_pos;
    Vector *head_pos = get_snake_head(snake);

    if (!strcmp(direction, "down"))
    {
        new_pos.x = head_pos->x;    
        new_pos.y = (head_pos->y + 1) % SCREEN_HEIGHT;
    }

    if (!strcmp(direction, "up"))
    {
        new_pos.x = head_pos->x;    
        new_pos.y = head_pos->y == 0 ? SCREEN_HEIGHT - 1 : head_pos->y - 1;
    }

    if (!strcmp(direction, "left"))
    {
        new_pos.x = head_pos->x == 0 ? SCREEN_WIDTH - 1 : head_pos->x - 1;
        new_pos.y = head_pos->y;
    }

    if (!strcmp(direction, "right"))
    {
        new_pos.x = (head_pos->x + 1) % SCREEN_WIDTH;
        new_pos.y = head_pos->y;
    }

  return new_pos;
}


void snake_movement( SDL_Renderer *renderer, Snake_Node *snake, char *direction )
{

  Vector new_pos = peak_next_pos(snake, direction);

  Vector *head_pos = get_snake_head(snake);
  Vector old_pos = *head_pos;
  Vector tmp_pos = old_pos;

  *head_pos = new_pos;

  for (int i = snake->length - 2 ; i >= 0; i--) {
    tmp_pos = snake->body[i];
    snake->body[i] = old_pos;
    old_pos = tmp_pos;
  }

  render_snake( renderer, snake );

  SDL_Delay(1000/90);
}

