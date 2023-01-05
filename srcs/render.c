#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Render.h"
#include "Entity.h"
#include "Snake.h"



SDL_Window *window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
TTF_Font* font = NULL;
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

    window = SDL_CreateWindow( "Snake Game",
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

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }


    return success;
}

void game()
{

    Entity *apple = new_entity( vector2f(random_number(0, SCREEN_WIDTH - 32), random_number(0, SCREEN_HEIGHT - 32)), load_texture(renderer,"./static/ball.png") );
    
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    bool running = true;
    bool collsions = false;

    Snake_Node *snake = malloc(sizeof(Snake_Node));
    snake->body[0].x = SCREEN_WIDTH / 2;
    snake->body[0].y = SCREEN_HEIGHT / 2;
    snake->length = 1;

    int score = 0;
    char *direction = "up"; 
    
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
                        direction = "up";
                        break;
                    case SDLK_DOWN:
                        direction = "down";
                        break;
                    case SDLK_LEFT:
                       direction = "left";
                        break;
                    case SDLK_RIGHT:
                       direction = "right";
                        break;
                }
            }

        }


        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );
        load_text( font, renderer ,score );
        
        snake_movement( renderer ,snake, direction );

        if (
        snake->body->x + 20 > apple->x && snake->body->x < apple->x + apple->currentFrame.w &&
        snake->body->y + 20 > apple->y && snake->body->y < apple->y + apple->currentFrame.h
        )
        {
            Vector new_pos2 = peak_next_pos(snake, direction);
            score++;
            snake->length += 2;
            snake->body[snake->length - 1] = new_pos2;
            apple = new_entity( vector2f(random_number(0, SCREEN_WIDTH - 32), random_number(0, SCREEN_HEIGHT - 32)), load_texture( renderer, "./static/ball.png" ) );
        }

        render_texture( renderer, apple );
        SDL_RenderPresent( renderer );
    }


    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    TTF_CloseFont( font );

    window = NULL;
    renderer = NULL;
    font = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
