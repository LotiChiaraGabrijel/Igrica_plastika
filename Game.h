#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "player.h"
class Game {
	bool running;
    SDL_Window* window;
    SDL_Event ev;
    SDL_Renderer* renderer;
    SDL_Texture* testTexture;
    SDL_Rect destRect;
    Player *player;
public:
    Game();
    void init();
    void run();
    void clean();
};

