#define SDL_MAIN_HANDLED   // pove SDL, da ne bo prepisoval main
#include <SDL.h>
#include "Game.h"
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* argv[])
{
    Game game;
    game.init();
    game.run();
    game.clean();

    return 0;
}
