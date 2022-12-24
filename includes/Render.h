#ifndef RENDER_H
#define RENDER_H
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "Entity.h"

bool init();
// bool load_media();
// SDL_Surface* load_surface( const char* path );
SDL_Texture* load_texture( const char* path );

void render_texture( Entity *new_entity );
#endif