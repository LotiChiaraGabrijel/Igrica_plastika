#pragma once
#include "screen.h"
#include "player.h"
#include <SDL.h>
#include <SDL_image.h>
#include "ally.h"
#include <fstream>
#include "font.h"
#include <vector>
#include "ship.h"
#include "trash.h"
#include "enemy.h"
#include <string>


//game screen header
class GameScreen : public Screen {
	Player* player;
	Ship* ship;
	Entity* change;
	SDL_Texture* background;
	SDL_Renderer* renderer;
	int level;
	SDL_Rect destRect;
	int score;
	SDL_Surface* surface;
	std::vector<Trash *>  trash_arr;
	std::vector<Enemy*> enemy_arr;
	std::vector<Ally*> ally_arr;
	bool onWater,
		wasOnWater;
	SDL_Texture* font_tex;
	bool end;
	bool win;
	std::string name;
public:
	GameScreen(SDL_Renderer* renderer, std::string name);
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
	bool get_win();
	void ally_collision_player();
	void enemy_collision_player();
	void clear_level();
	void save_score();
	void next_level();
	~GameScreen();
};