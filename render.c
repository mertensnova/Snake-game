#include "includes/Render.h"
#include "includes/Entity.h"
#include <stdio.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include <stdbool.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
//The surface contained by the window
SDL_Surface* screenSurface = NULL;
//The window renderer
SDL_Renderer* renderer = NULL;
//Current displayed texture
SDL_Texture* texture = NULL;
bool init()
{
    //Initialization flag
	bool success = true;
    SDL_Event event;
    bool running = true;

    //Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
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
    }

    //Create renderer for window
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }

    SDL_Texture *ballTexture = load_texture("./pictures/ball.png");
    float x = 0;
    float y = 0 ;
    Entity *ball = new_entity(position(x,y),ballTexture);

    while ( running )
    {

        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
            {
                running = false;
                break;
            }
            else if ( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                case SDLK_UP:
                  y -= 10;
                  ball = new_entity(position(x,y),ballTexture);
                break;
                case SDLK_DOWN:
                    y += 10;
                    ball = new_entity(position(x,y),ballTexture);
                break;
                case SDLK_LEFT:
                    x -= 10;
                    ball = new_entity(position(x,y),ballTexture);
                break;
                case SDLK_RIGHT:
                    x += 10;
                    ball = new_entity(position(x,y),ballTexture);
                break;

                }       
            }
        }
        //Clear screen
        SDL_RenderClear( renderer );  

        render_texture( ball );

		SDL_RenderPresent( renderer );
    }

    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
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
