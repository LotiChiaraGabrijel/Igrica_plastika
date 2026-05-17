#include "death_screen.h"

DeathScreen::DeathScreen(SDL_Renderer* renderer) {
	background = IMG_LoadTexture(renderer, "slike/death.png");
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;
	reset = false;
	replay = false;
	reset_button = { 150, 200, 256, 256 };
	replay_button = { 600, 200, 256, 256 };
	reset_tex = IMG_LoadTexture(renderer, "slike/restart.png");
	replay_tex = IMG_LoadTexture(renderer, "slike/replay.png");
}
void DeathScreen::render(SDL_Renderer* renderer) {

	SDL_RenderCopy(renderer, background, nullptr, &destRect);
	SDL_RenderCopy(renderer, reset_tex, nullptr, &reset_button);
	SDL_RenderCopy(renderer, replay_tex, nullptr, &replay_button);

}

bool DeathScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int mouseX = e.button.x;
		int mouseY = e.button.y;

		if (mouseX >= reset_button.x && mouseX <= reset_button.x + reset_button.w &&
			mouseY >= reset_button.y && mouseY <= reset_button.y + reset_button.h) {
			reset = true;
		}
		else if (mouseX >= replay_button.x && mouseX <= replay_button.x + replay_button.w &&
			mouseY >= replay_button.y && mouseY <= replay_button.y + replay_button.h) {
			replay = true;
		}
	}
	return 1;
}
void DeathScreen::update(float deltaTime) {
}
bool DeathScreen::get_reset() {
	return reset;
}

bool DeathScreen::get_replay() {
	return replay;
}

DeathScreen::~DeathScreen() {
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(reset_tex);
	SDL_DestroyTexture(replay_tex);

}