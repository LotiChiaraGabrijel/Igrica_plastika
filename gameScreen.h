#pragma once
#include "screen.h"
#include "player.h"
#include <SDL.h>
#include <SDL_image.h>
#include "ally.h"

#include "font.h"

#include "ship.h"
#include "trash.h"
#include "enemy.h"

//game screen header
class GameScreen : public Screen {
	Player* player;
	Ship* ship;
	Entity* change;
	SDL_Texture* background;
	SDL_Rect destRect;
	int score;
	SDL_Surface* surface;
	Trash* trash_arr[10];
	Enemy* enemy_arr[10];
	Ally* ally_arr[5];
	bool onWater,
		wasOnWater;
	SDL_Texture* font_tex;
	bool end;

public:
	GameScreen(SDL_Renderer* renderer);
	void init_enemy_trash(SDL_Renderer* renderer);
	void init_ally(SDL_Renderer* renderer);
	void update_enemy_trash(float deltaTime);
	void update_ally(float deltaTime);
	void update_player(float deltaTime);
	bool handleEvents(SDL_Event& e) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
	bool is_on_water(int x, int y);
	bool check_collision(SDL_Rect a, SDL_Rect b);
	void draw_score(SDL_Renderer* renderer);
	bool get_end();
	~GameScreen();
};