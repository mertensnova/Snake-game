#include "includes/Render.h"
#include "includes/Entity.h"
#include <stdio.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include <stdbool.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
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
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
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

    SDL_Texture* grass = load_texture("./ground_grass_1.png");

    while ( running )
    {
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
            {
                running = false;
                break;
            }               
        }

        //Clear screen
        SDL_RenderClear( renderer );
        Entity *grass_texture = new_entity(100,100, grass);
       
        // Render 
        render_texture( grass_texture );
        //Update screen
        SDL_RenderPresent( renderer );
    }

    
    SDL_DestroyTexture( texture );
    //Destroy window    
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    return success;
}

bool load_media()
{
    //Loading success flag
    bool success = true;

    //Load PNG texture
    texture = load_texture( "./ground_grass_1.png" );
    if( texture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    return success;
}

void render_texture( Entity *pos )
{

    SDL_Rect src;
    src.x = pos->currentFrame.x; 
    src.y = pos->currentFrame.y;
    src.w = pos->currentFrame.w;
    src.h = pos->currentFrame.h;

    SDL_Rect dst;
    dst.x = pos->x; 
    dst.y = pos->y;
    dst.w = pos->currentFrame.w * 4;
    dst.h = pos->currentFrame.h * 4;

    SDL_RenderCopy( renderer, pos->tex, &src, &dst );

}

SDL_Texture* load_texture( const char* path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    newTexture  = IMG_LoadTexture( renderer,path );
    if ( newTexture == NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );


    return newTexture;
}
