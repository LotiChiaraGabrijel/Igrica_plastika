#pragma once
#include "screen.h"
#include <SDL.h>
#include <SDL_image.h>
#include "font.h"
#include <string>
#include <iostream>
#include <vector>

class WinScreen : public Screen {
	SDL_Rect destRect;
	SDL_Texture* background;
	SDL_Texture* font_tex;
	bool reset;
	bool replay;
	SDL_Rect reset_button;
	SDL_Texture* reset_tex;
	SDL_Rect replay_button;
	SDL_Texture* replay_tex;

public:
	WinScreen(SDL_Renderer*);
	bool handleEvents(SDL_Event& e) override;
	void update(float deltaTime) override;
	void sort_scores_file();
	void display_score(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer) override;
	bool get_reset();
	bool get_replay();
	bool is_in_vector(char name[30], std::vector<const char*> vec);

	~WinScreen();
};