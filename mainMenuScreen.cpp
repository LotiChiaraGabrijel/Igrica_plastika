#include "MainMenuScreen.h"
#include <iostream>
#include <SDL_image.h>


MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer) {
	SDL_StartTextInput();
	startGame = false;
	name = "";
	background = IMG_LoadTexture(renderer, "slike/ozdadje_menu.png");

}

bool MainMenuScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_TEXTINPUT) {
		name.append(e.text.text);
	}
	if (e.type == SDL_KEYDOWN && name.length() > 0 && e.key.keysym.sym == SDLK_BACKSPACE)
		name.pop_back();
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
	{
		startGame = true;
	}
		
	if (e.type == SDL_QUIT) return 0;
	return 1;
}
void MainMenuScreen::update(float deltaTime) {

}
void MainMenuScreen::render(SDL_Renderer* renderer) {
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;
	SDL_RenderCopy(renderer, background, nullptr, &destRect);
}
MainMenuScreen::~MainMenuScreen() {
	SDL_StopTextInput();

}

bool MainMenuScreen::get_start() {
	return startGame;
}