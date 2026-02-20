#pragma once
#include <string>
#include "screen.h"
#include <SDL.h>

//Main menu header

class MainMenuScreen : public Screen {
	std::string name;
	bool startGame;
public:
	MainMenuScreen(SDL_Renderer*);
	bool handleEvents(SDL_Event& e) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
	bool get_start();
	~MainMenuScreen();
};