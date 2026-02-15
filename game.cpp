#include "Game.h"
#include <SDL.h>
Game::Game() {
    running = false;
    window = nullptr;
    renderer = nullptr;
}

void Game::init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL2 Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, 0);
    running = true;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::run() {
    while (running) {
        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT)
                running = false;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
