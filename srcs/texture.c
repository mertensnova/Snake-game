#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "Entity.h"

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
