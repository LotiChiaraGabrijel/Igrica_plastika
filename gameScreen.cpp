#include "gameScreen.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
//gameScreen.cpp
GameScreen::GameScreen(SDL_Renderer* renderer, string name) {
	this->name = name;
	player = new Player(renderer);
	ship = new Ship(renderer);
	player->loadTexture();
	ship->loadTexture();
	change = player;
	score = 0;
	onWater = false;
	this->renderer = renderer;
	level = 1;
	wasOnWater = false;
	game_time = 0;
	font_tex = load_font(renderer);
	surface = IMG_Load("slike/mask.png");
	end = false;
	win = false;
	if (!surface) std::cout << IMG_GetError();
	background = IMG_LoadTexture(renderer, "slike/background.png");
	trash_arr.resize(10);
	enemy_arr.resize(10);
	ally_arr.resize(5);
	init_enemy_trash(renderer);
	init_ally(renderer);

}

bool GameScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	return 1;
}
void GameScreen::update(float deltaTime) {
	game_time += deltaTime;
	change->update(deltaTime);
		//check enemy on water
	update_enemy_trash( deltaTime);
	update_ally( deltaTime);
	update_player( deltaTime);
	//next level when all enemies and trash are destroyed
	if (trash_arr.empty() && enemy_arr.empty()) {
		clear_level();

		if (level == 1) {
			win = true;
			save_score();
			return;
		}
		next_level();
	}
}

void GameScreen::update_player(float deltaTime) {
	int checkX, checkY;
	checkX = change->get_x() + 50;
	checkY = change->get_y() + 99;
	if (is_on_water(checkX, checkY)) {
		onWater = true; 
			vector<Trash*>::iterator it;
			for (it = trash_arr.begin(); it != trash_arr.end();)
				if (change->check_collision((*it)->get_rect()) && (*it)->get_alive() == true) {
					score += 10;
					delete* it;
					it = trash_arr.erase(it);
				}
				else
					++it;
	}
	else {
		onWater = false;
		enemy_collision_player();
		ally_collision_player();
	}
	if (onWater != wasOnWater) {
		if (onWater == true) {

			ship->set_x(player->get_x());
			ship->set_y(player->get_y());
			change = ship;
		}
		else {
			player->set_x(ship->get_x());
			player->set_y(ship->get_y());
			change = player;
		}
		wasOnWater = onWater;
	}
}

void GameScreen::enemy_collision_player() {
	vector<Enemy*>::iterator it;

	for (it = enemy_arr.begin(); it != enemy_arr.end();)
		if (change->check_collision((*it)->get_rect()) && (*it)->get_alive() == true) {
			if ((*it)->get_together() == true) {
				end = true;
				return;
			}
			else {
				score += 10;
				delete* it;
				it = enemy_arr.erase(it);

			}
		}
		else
			++it;
}
void GameScreen:: ally_collision_player() {
	for (vector<Ally*>::iterator it = ally_arr.begin(); it != ally_arr.end(); it++)
		if (change->check_collision((*it)->get_rect()) && (*it)->get_alive() == true) {
			score -= 10;
			(*it)->set_alive(false);
		}
}


void GameScreen::update_ally(float deltaTime) {
	int checkX, checkY;
	for (vector<Ally*>::iterator it = ally_arr.begin(); it != ally_arr.end(); it++)  {
		float oldX = (*it)->get_x(),
			oldY = (*it)->get_y();
		checkX = (*it)->get_x();
		checkY = (*it)->get_y();
		if (is_on_water(checkX + 25, checkY + 75) == true || is_on_water(checkX, checkY + 75) ==
			true || is_on_water(checkX + 49, checkY + 75) == true) {
			(*it)->set_x(oldX);
			(*it)->set_y(oldY);
			(*it)->change_dir();
		}
		(*it)->update(deltaTime);
	}
}

void GameScreen::update_enemy_trash(float deltaTime) {
	//update position of enemy
	for (vector<Enemy*>::iterator it = enemy_arr.begin(); it != enemy_arr.end(); it++) {
		float oldX = (*it)->get_x(),
			oldY = (*it)->get_y();
		(*it)->update(deltaTime);

		int checkX = (*it)->get_x();
		int checkY = (*it)->get_y();
		if (is_on_water(checkX + 25, checkY + 75) == true || is_on_water(checkX, checkY + 75) ==
			true || is_on_water(checkX + 49, checkY + 75) == true) {
			(*it)->set_x(oldX);
			(*it)->set_y(oldY);
			(*it)->change_dir();

		}
		//check if enemy is in radius and set visibility
		if ((*it)->is_in_radius(change->get_rect())) {
			(*it)->set_visible(true);
		}
		else {
			(*it)->set_visible(false);

		}
	}
	for (vector<Trash*>::iterator it = trash_arr.begin(); it != trash_arr.end(); it++) {
		//update position of trash

		int oldX = (*it)->get_x(),
			oldY = (*it)->get_y();
		(*it)->update(deltaTime);
		int checkX = (*it)->get_x();
		int checkY = (*it)->get_y();
		if (is_on_water(checkX + 25, checkY + 75) == false) {
			(*it)->set_x(oldX);
			(*it)->set_y(oldY);
			(*it)->change_dir();
		}
	}


	//checking all enemies with eachother
	for (vector<Enemy*>::iterator it = enemy_arr.begin(); it != enemy_arr.end(); it++) {
		(*it)->set_together(false);
	}
	for (vector<Enemy*>::iterator it = enemy_arr.begin(); it != enemy_arr.end(); it++) {
		(*it)->set_together(false);
	}

	for (vector<Enemy*>::iterator it = enemy_arr.begin(); it != enemy_arr.end(); it++) {
		for (vector<Enemy*>::iterator it2 = it + 1; it2 != enemy_arr.end(); it2++) {
			if ((*it)->check_collision((*it2)->get_rect()) &&
				(*it)->get_alive() == true &&
				(*it2)->get_alive() == true) {

				(*it)->set_together(true);
				(*it2)->set_together(true);
			}
		}
	}
}

void GameScreen::render(SDL_Renderer* renderer) {
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;
	SDL_RenderCopy(renderer, background, nullptr, &destRect);
	change->render();
	for (vector<Enemy*>::iterator it = enemy_arr.begin(); it != enemy_arr.end(); it++)
		(*it)->render();
	for (vector<Trash*>::iterator it = trash_arr.begin(); it != trash_arr.end(); it++)
		(*it)->render();
	for (vector<Ally*>::iterator it = ally_arr.begin(); it != ally_arr.end(); it++)
		(*it)->render();



	destRect.w = 500;
	destRect.h = 500;
	destRect.x = 96;
	destRect.y = 96;
	draw_score_level_time(renderer);

}

bool GameScreen::is_on_water(int x, int y) {
	if (x < 0) x = 0;
	else if (x > surface->w) x = surface->w - 1;
	if (y < 0) y = 0;
	else if (y > surface->h) y = surface->h - 1;
	Uint8* pixels = (Uint8*)surface->pixels;
	int pitch = surface->pitch;
	int bytesPerPixel = surface->format->BytesPerPixel;
	Uint8* pixelAddr = pixels + y * pitch + x * bytesPerPixel;
	Uint32 pixel = *(Uint32*)pixelAddr;
	Uint8 r, g, b;
	SDL_GetRGB(pixel, surface->format, &r, &g, &b);
	if (r < 50) return 1;
	else return 0;

}


void GameScreen::draw_score_level_time(SDL_Renderer* renderer) {
	std::string number;
	if (score >= 100)
		number = (score % 100) + (score % 10) + '0';
	else
		number = '0' + (score % 100) + (score % 10);
	number = std::to_string(score);
	draw_text(renderer, font_tex,number, 20, 20, 2);
	draw_text(renderer, font_tex, "level "+ to_string(level), 850, 20, 2);
	draw_text(renderer, font_tex, to_string(game_time), 20, 50, 2);


}

void GameScreen::init_enemy_trash(SDL_Renderer* renderer) {
	int checkX, checkY;
	for (vector<Enemy*>::iterator it = enemy_arr.begin(); it != enemy_arr.end(); it++) {
		(*it) = new Enemy(renderer, surface);
		do {
			checkX = rand() % 975 + 75;
			checkY = rand() % 450 + 75;
			(*it)->set_x(checkX);
			(*it)->set_y(checkY);
		} while (is_on_water(checkX + 25, checkY + 75) == true || is_on_water(checkX, checkY + 75) ==
			true || is_on_water(checkX + 49, checkY + 75) == true);
		(*it)->loadTexture();

	}


	for (vector<Trash*>::iterator it = trash_arr.begin(); it != trash_arr.end(); it++) {
		(*it) = new Trash(renderer);

		do {
			checkX = rand() % 924 + 50;
			checkY = rand() % 850 + 50;
			(*it)->set_x(checkX);
			(*it)->set_y(checkY);
		} while (is_on_water(checkX + 25, checkY) == false);
		(*it)->loadTexture();
	}
}

void GameScreen:: init_ally(SDL_Renderer* renderer) {
	int checkX, checkY;

	for (vector<Ally*>::iterator it = ally_arr.begin(); it != ally_arr.end(); it++) {
		(*it) = new Ally(renderer, surface);

		do {
			checkX = rand() % 975 + 75;
			checkY = rand() % 450 + 75;
			(*it)->set_x(checkX);
			(*it)->set_y(checkY);
		} while (is_on_water(checkX + 25, checkY + 75) == true || is_on_water(checkX, checkY + 75) ==
			true || is_on_water(checkX + 49, checkY + 75) == true);
		(*it)->loadTexture();

	}
}

bool GameScreen::get_end() {
	return end;
}

void GameScreen::next_level() {
	++level;
	trash_arr.resize(10 + level * 2);
	enemy_arr.resize(10 + level * 2);
	ally_arr.resize(5);
	game_time = 0;

	init_enemy_trash(renderer);
	init_ally(renderer);
}
void GameScreen::clear_level() {
	for (vector<Ally*>::iterator it = ally_arr.begin(); it != ally_arr.end();) {
		delete* it;
		it = ally_arr.erase(it);
	}
	if (game_time <25) score += 200;
	else if (game_time < 50) score += 150;
	else if (game_time < 75) score += 50;
}
struct player_info {
	char name_player[30];
	int score_player;
};
void GameScreen::save_score() {
	player_info info;
	strncpy_s(info.name_player, sizeof(info.name_player), name.c_str(), _TRUNCATE);
	info.score_player = score;
	ofstream file("scores.dat", ios::binary | ios::app);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(&info), sizeof(info));
		file.close();
	}
}

bool GameScreen::get_win() {
	return win;
}

GameScreen::~GameScreen() {
	delete ship;
	delete player;
	SDL_DestroyTexture(font_tex);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(background); 
	for (vector<Trash*>::iterator it = trash_arr.begin(); it != trash_arr.end();) {
		delete* it;
		it = trash_arr.erase(it);
	}

	for (vector<Enemy*>::iterator it = enemy_arr.begin(); it != enemy_arr.end();) {
		delete* it;
		it = enemy_arr.erase(it);
	}

	for (vector<Ally*>::iterator it = ally_arr.begin(); it != ally_arr.end();) {
		delete* it;
		it = ally_arr.erase(it);
	}


}