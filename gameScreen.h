#pragma once
#include "screen.h"
#include "player.h"
#include <SDL.h>
#include <SDL_image.h>


//game screen header
class GameScreen : public Screen {
	Player* player;
	SDL_Texture* background;
	SDL_Rect destRect;
	SDL_Surface* surface;

public:
	GameScreen(SDL_Renderer* renderer);
	bool handleEvents(SDL_Event& e) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
	~GameScreen();
};