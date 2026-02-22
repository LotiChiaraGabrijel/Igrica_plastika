#pragma once
#include "screen.h"
#include "player.h"
#include <SDL.h>
#include <SDL_image.h>
#include "ship.h"

//game screen header
class GameScreen : public Screen {
	Player* player;
	Ship* ship;
	Entity* change;
	SDL_Texture* background;
	SDL_Rect destRect;
	SDL_Surface* surface;
	bool onWater,
		wasOnWater;

public:
	GameScreen(SDL_Renderer* renderer);
	bool handleEvents(SDL_Event& e) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
	~GameScreen();
};