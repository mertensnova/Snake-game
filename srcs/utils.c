#include <time.h>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

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

// bool load_media()
// {
//     //Loading success flag
//     bool success = true;

//     //Open the font
//     font = TTF_OpenFont( "../static/font/font.ttf", 28 );
//     if( font == NULL )
//     {
//         printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
//         success = false;
//     }
//     else
//     {
//         //Render text
//         SDL_Color textColor = { 0, 0, 0 };
//         if( !gTextTexture.loadFromRenderedText( "The quick brown fox jumps over the lazy dog", textColor ) )
//         {
//             printf( "Failed to render text texture!\n" );
//             success = false;
//         }
//     }

//     return success;
// }

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
