#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.h" 


void render_texture( SDL_Renderer *renderer ,Entity *new_entity );
SDL_Texture* load_texture( SDL_Renderer *renderer , const char* path); 
int random_number(int min_num, int max_num);


bool load_text( TTF_Font* font ,SDL_Renderer * renderer , int score );


#endif
