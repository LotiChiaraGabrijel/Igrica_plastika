#pragma once
#include <SDL.h>
class Game {
	bool running;
    SDL_Window* window;
    SDL_Event ev;
    SDL_Renderer* renderer;
public:
    Game();
    void init();
    void run();
    void clean();
};

