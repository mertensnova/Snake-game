#ifndef RENDER_H
#define RENDER_H
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "Entity.h"


//Screen dimension constants
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (480)
#define SPEED  (300)

bool init();
// bool load_media();
// SDL_Surface* load_surface( const char* path );
SDL_Texture* load_texture( const char* path );

void render_texture( Entity *new_entity );
#endif