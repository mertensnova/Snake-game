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
	
    int window_refresh_rate = get_refresh_rate();
    printf("%d\n",window_refresh_rate);

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
    SDL_Texture *grassTexture = load_texture("./ground_grass_1.png");

    Entity *entities[50] = {
        new_entity( position(300 , SCREEN_HEIGHT - 150), grassTexture ),
        new_entity( position(200 , SCREEN_HEIGHT - 150), grassTexture ),
        new_entity( position(150 ,SCREEN_HEIGHT - 150), grassTexture ),
        new_entity( position(150 ,SCREEN_HEIGHT - 150), grassTexture ),
        new_entity( position(150 ,SCREEN_HEIGHT - 150), grassTexture ),
    }; 

    const float time_step = 0.01f;
    float accmulator = 0.0f;
    float current_time = SDL_GetTicks();

    while ( running )
    {
        int start_tick = SDL_GetTicks();

        float new_time = SDL_GetTicks();
        float frame_time = new_time - current_time;
        
        current_time = new_time;

        accmulator += frame_time;
        while (accmulator >= time_step)
        {
            while ( SDL_PollEvent( &event ) )
            {
                if ( event.type == SDL_QUIT )
                {
                    running = false;
                    break;
                }               
            }
            accmulator -= time_step;  
        }
         
         const float alpha  = accmulator / time_step;

        //Clear screen
        SDL_RenderClear( renderer );  
        // Render all entities
        for (int i = 0; i < 5; i++)
            render_texture( entities[i] );
            
        //Update screen
        SDL_RenderPresent( renderer );
        int frame_ticks = SDL_GetTicks() - start_tick;

        if ( frame_ticks < 1000 / get_refresh_rate() )
           SDL_Delay( 1000 / window_refresh_rate - frame_ticks );
    }

    
    SDL_DestroyTexture( texture );
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
    dst.w =  new_entity->currentFrame.w * 4;
    dst.h = new_entity->currentFrame.h * 4;

    SDL_RenderCopy( renderer, new_entity->tex, &src, &dst );

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

int get_refresh_rate()
{
    int display_index = SDL_GetWindowDisplayIndex( window );

    SDL_DisplayMode mode;

    SDL_GetDisplayMode( display_index ,0 ,&mode );
    return mode.refresh_rate;
}
