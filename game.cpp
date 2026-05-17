#include "Game.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "gameScreen.h"
#include "MainMenuScreen.h"
#include <ctime>
#include "death_screen.h"
#include "win_screen.h"


Game::Game() {
    running = false;
    window = nullptr;
    renderer = nullptr;
}

void Game::init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Igra Izbriši plastiko",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1024, 900, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    currentScreen = new MainMenuScreen(renderer);
    running = true;


}

void Game::run() {
    Uint32 startTime = SDL_GetTicks(), lastTime;
    float deltaTime = 0;
    while (running) {
        lastTime = startTime;
        startTime = SDL_GetTicks();
        while (SDL_PollEvent(&ev)) {
            if (currentScreen->handleEvents(ev) == 0)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        deltaTime = (startTime - lastTime) / 1000.0f;
        currentScreen->update(deltaTime);
        if (dynamic_cast<MainMenuScreen*>(currentScreen)) {
            MainMenuScreen* menu = dynamic_cast<MainMenuScreen*>(currentScreen);
            if (menu->get_start())
            {
                name = menu->get_name();
                delete currentScreen;
                currentScreen = new GameScreen(renderer, name, false);

            }

        }
        if (dynamic_cast<GameScreen*>(currentScreen)) {
            GameScreen* game = dynamic_cast<GameScreen*>(currentScreen);

            if (game->get_end()) {
                delete currentScreen;
                currentScreen = new DeathScreen(renderer);
            }
            else if (game->get_win()) {
                delete currentScreen;
                currentScreen = new WinScreen(renderer);
            }
        }
        if (dynamic_cast<DeathScreen*>(currentScreen)) {
            DeathScreen* death = dynamic_cast<DeathScreen*>(currentScreen);

            if (death->get_reset()) {
                delete currentScreen;
                currentScreen = new GameScreen(renderer, name, false);

            }
            else if (death->get_replay()) {
                delete currentScreen;
                currentScreen = new GameScreen(renderer, name, true);
            }

        }
        else if (dynamic_cast<WinScreen*>(currentScreen)) {
            WinScreen* win = dynamic_cast<WinScreen*>(currentScreen);

            if (win->get_reset()) {
                delete currentScreen;
                currentScreen = new GameScreen(renderer, name, false);
            }
            else if (win->get_replay()) {
                delete currentScreen;
                currentScreen = new GameScreen(renderer, name, true);
            }
        }
        currentScreen->render(renderer);

        SDL_RenderPresent(renderer);
    }

}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete currentScreen;
    IMG_Quit();
    SDL_Quit();
}
