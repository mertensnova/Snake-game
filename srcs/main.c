#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"

#include "Render.h"

int main(void)
{

    if ( !init() )
    {
        printf( "Failed to initialize! \n");
        return 1;
    }
    else
        game();

    return 0;
}