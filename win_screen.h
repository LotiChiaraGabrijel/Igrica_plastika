#pragma once
#include "screen.h"
#include <SDL.h>
#include <SDL_image.h>


class WinScreen : public Screen {
	SDL_Rect destRect;
	SDL_Texture* background;

public:
	WinScreen(SDL_Renderer*);
	bool handleEvents(SDL_Event& e) override;
	void update(float deltaTime) override;

	void render(SDL_Renderer* renderer) override;
	~WinScreen();
};