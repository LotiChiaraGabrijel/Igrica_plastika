#include "Game.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

Game::Game() {
    running = false;
    window = nullptr;
    renderer = nullptr;
    player = nullptr;
}

void Game::init() {
    // Ustvari okno in renderer
    window = SDL_CreateWindow("Igra Izbriši plastiko",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1000, 800, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    running = true;

    // Inicializacija Player-ja
    player = new Player(renderer);      // ustvari Player z rendererjem
    player->loadTexture();  // naloži Player PNG
}

void Game::run() {
    Uint32 startTime = SDL_GetTicks(), lastTime;
    float deltaTime = 0;
    while (running) {
        lastTime = startTime;
        startTime = SDL_GetTicks();
        // Poll dogodki
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT)
                running = false;
        }

        // Clear zaslon
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Update in render player
        player->update((startTime - lastTime) / 1000.0f);
        player->render();

        // Future: render other entities, smeti, nasprotnike, zavezence itd.

        SDL_RenderPresent(renderer);
    }
}

void Game::clean() {
    delete player;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}
