#include "win_screen.h"

WinScreen::WinScreen(SDL_Renderer* renderer) {
	background = IMG_LoadTexture(renderer, "slike/win.png");
}
void WinScreen::render(SDL_Renderer* renderer) {
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;
	SDL_RenderCopy(renderer, background, nullptr, &destRect);
}

bool WinScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	return 1;
}
void WinScreen::update(float deltaTime) {
}


WinScreen::~WinScreen() {

}