#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "includes/Render.h"
#include "includes/Entity.h"
#include "includes/Snake.h"


SDL_Window *window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

//Current displayed texture
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

    Entity *snake = new_entity( vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), load_texture("./static/ball.png") );
    Entity *apple = new_entity( vector2f(random_number(0, SCREEN_WIDTH - 32), random_number(0, SCREEN_HEIGHT - 32)), load_texture("./static/tile32_dark.png") );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    bool running = true;
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

        snake_movement( snake, up,  down, left, right );

        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        render_texture( snake );
        render_texture( apple );

        if (
            snake->x + snake->currentFrame.w > apple->x && snake->x < apple->x + apple->currentFrame.w &&
            snake->y + snake->currentFrame.h > apple->y && snake->y < apple->y + apple->currentFrame.h
           )
        {   
            score++;
            apple = new_entity( vector2f(random_number(0, SCREEN_WIDTH - 32), random_number(0, SCREEN_HEIGHT - 32)), load_texture("./static/tile32_dark.png") );  
        }
        
        render_texture( apple );
        SDL_RenderPresent( renderer );
    }

    printf("%d\n",score);
    
    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return success;
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
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    newTexture  = IMG_LoadTexture( renderer, path );

    if ( newTexture == NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );


    return newTexture;
}
