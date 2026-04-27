#include "death_screen.h"

DeathScreen::DeathScreen(SDL_Renderer* renderer) {
	background = IMG_LoadTexture(renderer, "slike/death.png");
}
void DeathScreen::render(SDL_Renderer* renderer) {
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;
	SDL_RenderCopy(renderer, background, nullptr, &destRect);
}

bool DeathScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	return 1;
}
void DeathScreen::update(float deltaTime) {
}


DeathScreen::~DeathScreen() {

}