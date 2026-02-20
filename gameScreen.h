#pragma once
#include "screen.h"
#include "player.h"
#include <SDL.h>

//game screen header
class GameScreen : public Screen {
	Player* player;
public:
	GameScreen(SDL_Renderer* renderer);
	bool handleEvents(SDL_Event& e) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
	~GameScreen();
};