#pragma once
#include <string>
#include "screen.h"
#include <SDL.h>
#include "font.h"

//Main menu header

class MainMenuScreen : public Screen {
	std::string name;
	bool startGame;
	SDL_Rect destRect;
	SDL_Rect start;
	SDL_Texture* start_button;
	SDL_Texture* font_tex;
	SDL_Texture* background;

public:
	MainMenuScreen(SDL_Renderer*);
	bool handleEvents(SDL_Event& e) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
	bool get_start();
	std::string get_name();
	~MainMenuScreen();
};