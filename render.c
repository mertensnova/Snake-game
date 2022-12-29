#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "includes/Render.h"
#include "includes/Entity.h"
#include "includes/Snake.h"


SDL_Window *window = NULL;

SDL_Surface* screenSurface = NULL;

SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;

SDL_Event event;

int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

bool init()
{
     //Initialization flag
	bool success = true;

    //Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
        exit(1);
    }
  
    window = SDL_CreateWindow( "My World", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, 
                                SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
	    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        success = false;
        exit(1);
    }

    //Create renderer for window
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
        exit(1);
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }

    return success;
}

void game()
{
   
    Entity *snake = new_entity( vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), load_texture("./static/tile32_dark.png") );
    Entity *bg = new_entity( vector2f(0,0), load_texture("./static/bg.png") );
    Entity *apple = new_entity( vector2f(random_number(0, SCREEN_WIDTH - 32), random_number(0, SCREEN_HEIGHT - 32)), load_texture("./static/ball.png") );
    // SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    bool running = true;
    bool collsions = false;
    SDL_Rect rect;
    rect.x = 250;
    rect.y = 150;
    rect.w = 50;
    rect.h = 20;


    int score = 0;
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    while ( running )
    {
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
            {
                running = false;
                break;
            }
            else if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:
                        up = 1;
                        down = 0;
                        left= 0;
                        right = 0;
                        break;
                    case SDLK_DOWN:
                        up = 0;
                        down = 1;
                        left= 0;
                        right = 0;
                        break;
                    case SDLK_LEFT:
                        up = 0;
                        down = 0;
                        left= 1;
                        right = 0;
                        break;
                    case SDLK_RIGHT:
                        up = 0;
                        down = 0;
                        left= 0;
                        right = 1;
                        break;
                }  
            }
            
        }

        SDL_RenderClear(renderer);
        snake_movement(&rect ,renderer,up,  down, left, right,score);

    
        if (
            rect.x + rect.w > apple->x && rect.x < apple->x + apple->currentFrame.w &&
            rect.y + rect.h > apple->y && rect.y < apple->y + apple->currentFrame.h
           )
        {   
            score++;
            collsions = true;
            apple = new_entity( vector2f(random_number(0, SCREEN_WIDTH - 32), random_number(0, SCREEN_HEIGHT - 32)), load_texture("./static/ball.png") );  
        }
        
        render_texture( apple );
        SDL_RenderPresent( renderer );
    }

    printf("Your Score : %d\n",score);
    
    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}


void render_texture( Entity *new_entity )
{
    SDL_Rect src;
    src.x = new_entity->currentFrame.x; 
    src.y = new_entity->currentFrame.y;
    src.w = new_entity->currentFrame.w;
    src.h = new_entity->currentFrame.h;

    SDL_Rect dst;
    dst.x = new_entity->x;
    dst.y = new_entity->y;
    dst.w =  new_entity->currentFrame.w;
    dst.h = new_entity->currentFrame.h;


    SDL_RenderCopy( renderer, new_entity->tex, &src, &dst );
}

SDL_Texture* load_texture( const char* path )
{
    SDL_Texture* newTexture = NULL;

    newTexture  = IMG_LoadTexture( renderer, path );

    if ( newTexture == NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );

    return newTexture;
}
