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
SDL_Texture* load_texture( const char* path );
// void set_pos(SDL_Texture *texture);

void render_texture( Entity *new_entity );
bool game_loop();
void close();
#endif