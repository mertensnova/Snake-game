#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>

#include "Entity.h" 


void render_texture( SDL_Renderer *renderer ,Entity *new_entity );
SDL_Texture* load_texture( SDL_Renderer *renderer ,const char* path); 




#endif
