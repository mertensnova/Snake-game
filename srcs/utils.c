#include <time.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.h"
#include "Utils.h"
#include "Render.h"


void render_texture( SDL_Renderer *renderer ,Entity *new_entity )
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

SDL_Texture* load_texture( SDL_Renderer *renderer ,const char* path )
{
    SDL_Texture* newTexture = NULL;

    newTexture  = IMG_LoadTexture( renderer, path );

    if ( newTexture == NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );

    return newTexture;
}

bool load_text( TTF_Font* font ,SDL_Renderer * renderer , int score )
{
    //Loading success flag
    bool success = true;
    char str[128];
    sprintf(str, "%d", score);

    //Open the font
    font = TTF_OpenFont( "./static/font.ttf", 128 );

    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    //Render text
    SDL_Color text_color = { 255, 255, 255 };
    SDL_Surface *surface_text = TTF_RenderText_Solid( font , "SCORE: ", text_color );
    SDL_Surface *score_text = TTF_RenderText_Solid( font , str, text_color );
    SDL_Texture *score_texture_text = SDL_CreateTextureFromSurface( renderer ,score_text );
    SDL_Texture *surface_texture_text = SDL_CreateTextureFromSurface( renderer ,surface_text );
    SDL_FreeSurface( score_text );
    SDL_FreeSurface( surface_text );

    SDL_Rect score_rect;
    score_rect.x = 100;
    score_rect.y  = 20;
    score_rect.h = 20;
    score_rect.w = 10;

    SDL_Rect surface_rect;
    surface_rect.x = 20;
    surface_rect.y  = 20;
    surface_rect.h = 20;
    surface_rect.w = 80;

    SDL_RenderCopy( renderer, score_texture_text ,NULL ,&score_rect );
    SDL_RenderCopy( renderer, surface_texture_text ,NULL ,&surface_rect );

    return success;
}

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
