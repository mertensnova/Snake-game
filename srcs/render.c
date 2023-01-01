#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "Render.h"
#include "Entity.h"
#include "Snake.h"
#include "Utils.h"
#include "Deque.h"


SDL_Window *window = NULL;

SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
SDL_Event event;


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

    // Entity *snake = new_entity( vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), load_texture(renderer,"./static/tile32_dark.png") );
    // Entity *bg = new_entity( vector2f(0,0), load_texture(renderer,"./static/bg.png") );
    // Entity *apple = new_entity( vector2f(random_number(0, SCREEN_WIDTH - 32), random_number(0, SCREEN_HEIGHT - 32)), load_texture(renderer,"./static/ball.png") );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    bool running = true;
    bool collsions = false;

    Deque *snake = deque_init();

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

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        
        draw_snake( snake, renderer,  up,  down, left, right);
        // snake_movement( renderer ,snake, up,  down, left, right );

        SDL_RenderPresent( renderer );
    }


    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}
