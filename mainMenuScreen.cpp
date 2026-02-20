#include "MainMenuScreen.h"
#include <iostream>
MainMenuScreen::MainMenuScreen(SDL_Renderer*) {
	SDL_StartTextInput();
	startGame = false;
	name = "";
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
}
void MainMenuScreen::update(float deltaTime) {

}
void MainMenuScreen::render(SDL_Renderer* renderer) {

}
MainMenuScreen::~MainMenuScreen() {
	SDL_StopTextInput();

}

bool MainMenuScreen::get_start() {
	return startGame;
}