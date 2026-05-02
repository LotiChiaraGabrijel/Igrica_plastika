#include "MainMenuScreen.h"
#include <iostream>
#include <SDL_image.h>


MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer) {
	SDL_StartTextInput();
	startGame = false;
	name = "";
	start_button = IMG_LoadTexture(renderer, "slike/start.png");
	start = { 270, 125, 512, 512 };
	background = IMG_LoadTexture(renderer, "slike/ozdadje_menu.png");
	font_tex = load_font(renderer);

}

bool MainMenuScreen::handleEvents(SDL_Event& e) {
	//name input
	if (e.type == SDL_TEXTINPUT) {
		name.append(e.text.text);
	}
	if (e.type == SDL_KEYDOWN && name.length() > 0 && e.key.keysym.sym == SDLK_BACKSPACE)
		name.pop_back();
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
		startGame = true;
	}
	//start button
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int mouseX = e.button.x;
		int mouseY = e.button.y;

		if (mouseX >= start.x && mouseX <= start.x + start.w &&
			mouseY >= start.y && mouseY <= start.y + start.h) {
			startGame = true;
		}
	}

	if (e.type == SDL_QUIT) return 0;
	return 1;
}
std::string MainMenuScreen::get_name() {
	return name;
}


void MainMenuScreen::update(float deltaTime) {

}
void MainMenuScreen::render(SDL_Renderer* renderer) {
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;

	SDL_RenderCopy(renderer, background, nullptr, &destRect);
	SDL_RenderCopy(renderer, start_button, nullptr, &start);

	draw_text(renderer, font_tex, name, 410, 160, 2);

}
MainMenuScreen::~MainMenuScreen() {
	SDL_StopTextInput();

}

bool MainMenuScreen::get_start() {
	return startGame;
}