#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "player.h"
#include "screen.h"

class Game {
	bool running;
    SDL_Window* window;
    SDL_Event ev;
    SDL_Renderer* renderer;
    SDL_Texture* testTexture;
    SDL_Rect destRect;
    Screen* currentScreen;
    std::string name;
public:
    Game();
    void init();
    void run();
    void clean();
};

