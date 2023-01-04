#include <time.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.h"
#include "Utils.h"


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

// bool load_rendered_text( char *textureText, SDL_Color textColor,TTF_Font* font, SDL_Renderer *renderer )
// {
//     //Get rid of preexisting texture
//     free();

//     //Render text surface
//     SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
//     if( textSurface == NULL )
//     {
//         printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
//     }
//     else
//     {
//         //Create texture from surface pixels
//         mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
//         if( mTexture == NULL )
//         {
//             printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
//         }
//         else
//         {
//             //Get image dimensions
//             mWidth = textSurface->w;
//             mHeight = textSurface->h;
//         }

//         //Get rid of old surface
//         SDL_FreeSurface( textSurface );
//     }
    
//     //Return success
//     return mTexture != NULL;
// }

bool load_media( TTF_Font* font ,SDL_Renderer * renderer )
{
    //Loading success flag
    bool success = true;

    //Open the font
    font = TTF_OpenFont( "../static/font/font.ttf", 28 );
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

        //Render text
    SDL_Color text_color = { 255, 255, 255 };
    SDL_Surface *surface_text = TTF_RenderText_Solid(font ,"Hello World",text_color);
    SDL_Texture *texture_text = SDL_CreateTextureFromSurface(renderer,surface_text);
    SDL_FreeSurface(surface_text);

    SDL_Rect rect;
    rect.x = 200;
    rect.y = 200;
    rect.h = 200;
    rect.w = 200;

    SDL_RenderCopy(renderer,texture_text,NULL,&rect);


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
