#include <stdio.h>
#include "SDL2/SDL.h"
#include <stdbool.h>
#include "includes/Render.h"
#include "includes/Entity.h"

int main(int argc,char *argv[])
{

    if ( !init() )
        printf( "Failed to initialize! \n");
    else
        game();

    return 0;
}

// // gcc -o main main.c -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2


