#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "includes/Render.h"
#include "includes/Entity.h"
#include "includes/Ball.h"


SDL_Window *window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

//Current displayed texture
SDL_Texture* texture = NULL;

int random_number(int min_num, int max_num)
{
        int result = 0, low_num = 0, hi_num = 0;

        if (min_num < max_num)
        {
            low_num = min_num;
            hi_num = max_num + 1; // include max_num in output
        } else {
            low_num = max_num + 1; // include max_num in output
            hi_num = min_num;
        }

        srand(time(NULL));
        result = (rand() % (hi_num - low_num)) + low_num;
        printf("%d\n",result);
        return result;
}

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
    SDL_Texture *tile_texture = load_texture("./pictures/tile32_dark.png");

    // Entity *ball = new_entity(position(0,0),ballTexture);
    // Entity *tiles = new_entity(position(random_number(0,SCREEN_WIDTH - 32), random_number(0,SCREEN_HEIGHT - 32)),tile_texture);
    
    SDL_Rect dest;
    SDL_Rect dest2;
    SDL_QueryTexture(ballTexture,NULL,NULL,&dest.w,&dest.h);
    SDL_QueryTexture(tile_texture,NULL,NULL,&dest2.w,&dest2.h);
    float x_vel = SPEED;
    float y_vel = SPEED;
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    dest2.x  =random_number(0,SCREEN_WIDTH - 20);
    dest2.y = random_number(0,SCREEN_HEIGHT - 20);

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
                        up =1;
                        break;
                    case SDLK_DOWN:
                        down = 1;
                        break;
                    case SDLK_LEFT:
                        left = 1;
                        break;
                    case SDLK_RIGHT:
                        right = 1;
                        break;
                }  
            }
        }

        // if (dest.x <= 0)
        //     dest.x = 0;

        // if (dest.y <= 0)
        //     dest.y = 0;
           
        // if (dest.x >= SCREEN_WIDTH - dest.w )
        //     dest.x = SCREEN_WIDTH -dest.w;
            
        // if (dest.y >= SCREEN_HEIGHT -dest.h )
        //    dest.y = SCREEN_HEIGHT -dest.h;
        float y_pos = SCREEN_HEIGHT;
        float x_pos = SCREEN_WIDTH;

        while (dest.y >= - dest.h)
        {
            SDL_RenderClear( renderer );
            dest.y = y_pos; 
            // dest.x = x_pos;
            // if(left && !right) x_pos--;
            // if(right && !left) x_pos++;
 
            SDL_RenderCopy(renderer,ballTexture,NULL, &dest);
            SDL_RenderPresent(renderer);
            if(up && !down) y_pos -= SPEED / 90; 
            if(down && !up) y_pos += SPEED / 90;
            SDL_Delay(1000/60);
        }
    
        // printf("TILES---------------->x:%d \t tiles->y:%d\n",dest2.x,dest2.y);
        // printf("BALLS------------>x:%d \t balss->y:%d\n",dest.x,dest.y);
        // if (dest.x == dest2.x)
        // {  
        //     printf("TRUE");
        //     // SDL_RenderClear( renderer );
        //     // SDL_RenderCopy( renderer ,tile_texture,NULL,&dest2);
        //     dest2.x  = random_number(0,SCREEN_WIDTH - 32);
        //     dest2.y = random_number(0,SCREEN_HEIGHT - 32);
        // }
        
           

        // SDL_RenderClear( renderer );
        // SDL_RenderCopy( renderer ,tile_texture,NULL,&dest2);
        // // SDL_RenderCopy( renderer ,ballTexture,NULL,&dest);
		// SDL_RenderPresent( renderer );
    }

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
