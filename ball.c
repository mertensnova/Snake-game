#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "includes/Entity.h"
#include "includes/Render.h"




// void set_pos(SDL_Renderer *renderer, SDL_Texture *texture)
// {
//     SDL_Rect dest;
//     float y_pos = SCREEN_HEIGHT;
//     float x_pos = SCREEN_WIDTH;

//     SDL_Texture *ballTexture = load_texture("./pictures/ball.png");
//     // SDL_RenderCopy( renderer ,tile_texture,NULL,&dest2);
//     // SDL_RenderCopy( renderer ,ballTexture,&src,&dest);
// 	SDL_RenderPresent( renderer );
    
//     // while (dest.y >=  -dest.h)
//     // {
//     //     SDL_RenderClear( renderer );  
//     //     // dest.y = (int) y_pos;

//     //     SDL_RenderCopy( renderer, ballTexture, NULL, &dest );
//     //     SDL_RenderPresent( renderer );

//     //     // y_pos -= (float) SPEED / 60;

//     //     // SDL_Delay(1000/60);
//     // }
// }