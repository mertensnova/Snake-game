#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"

#include "includes/Render.h"
#include "includes/Entity.h"
#include "includes/Texture.h"


int main(int argc,char *argv[])
{

    if ( !init() )
        printf( "Failed to initialize! \n");
    else
        game();

    return 0;
}
