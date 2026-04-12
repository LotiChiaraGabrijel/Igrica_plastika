#include "gameScreen.h"
#include <iostream>
#include <string>

//gameScreen.cpp
GameScreen::GameScreen(SDL_Renderer* renderer) {
	player = new Player(renderer);
	ship = new Ship(renderer);
	player->loadTexture();
	ship->loadTexture();
	change = player;
	score = 0;
	onWater = false;
	wasOnWater = false;
	font_tex = load_font(renderer);
	surface = IMG_Load("slike/mask.png");

	if (!surface) std::cout << IMG_GetError();
	background = IMG_LoadTexture(renderer, "slike/background.png");
	init_enemy_trash(renderer);
	init_ally(renderer);

}

bool GameScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	return 1;
}
void GameScreen::update(float deltaTime) {
	change->update(deltaTime);
		//check enemy on water
	update_enemy_trash( deltaTime);
	update_ally( deltaTime);
	update_player( deltaTime);
}

void GameScreen::update_player(float deltaTime) {
	int checkX, checkY;


	checkX = change->get_x() + 50;
	checkY = change->get_y() + 99;
	if (is_on_water(checkX, checkY))
	{
		onWater = true;
		for (int i = 0; i < 10; i++)
			if (change->check_collision(trash_arr[i]->get_rect()) && trash_arr[i]->get_alive() == true) {
				score += 10;
				trash_arr[i]->set_alive(false);
			}


	}
	else
	{
		onWater = false;
		for (int i = 0; i < 10; i++)
			if (change->check_collision(enemy_arr[i]->get_rect()) && enemy_arr[i]->get_alive() == true) {
				score += 10;
				enemy_arr[i]->set_alive(false);
			}
	}

	if (onWater != wasOnWater)
	{
		if (onWater == true)
		{

			ship->set_x(player->get_x());
			ship->set_y(player->get_y());
			change = ship;
		}

		else
		{
			player->set_x(ship->get_x());
			player->set_y(ship->get_y());
			change = player;
		}
		wasOnWater = onWater;
	}
}


void GameScreen::update_ally(float deltaTime) {
	int checkX, checkY;

	for (int i = 0; i < 5; i++) {
		float oldX = ally_arr[i]->get_x(),
			oldY = ally_arr[i]->get_y();
		checkX = ally_arr[i]->get_x();
		checkY = ally_arr[i]->get_y();
		if (is_on_water(checkX + 25, checkY + 75)) {
			ally_arr[i]->set_x(oldX);
			ally_arr[i]->set_y(oldY);
			ally_arr[i]->change_dir();
		}
		ally_arr[i]->update(deltaTime);
	}
}

void GameScreen::update_enemy_trash(float deltaTime) {

	for (int i = 0; i < 10; i++) {
		float oldX = enemy_arr[i]->get_x(),
			oldY = enemy_arr[i]->get_y();
		enemy_arr[i]->update(deltaTime);

		int checkX = enemy_arr[i]->get_x();
		int checkY = enemy_arr[i]->get_y();
		if (is_on_water(checkX + 25, checkY + 75)) {
			enemy_arr[i]->set_x(oldX);
			enemy_arr[i]->set_y(oldY);
			enemy_arr[i]->change_dir();

		}

		oldX = trash_arr[i]->get_x(),
			oldY = trash_arr[i]->get_y();
		trash_arr[i]->update(deltaTime);
		checkX = trash_arr[i]->get_x();
		checkY = trash_arr[i]->get_y();
		if (is_on_water(checkX + 25, checkY + 75) == false) {
			trash_arr[i]->set_x(oldX);
			trash_arr[i]->set_y(oldY);
			trash_arr[i]->change_dir();
		}

		if (enemy_arr[i]->is_in_radius(change->get_rect())) {
			enemy_arr[i]->set_visible(true);
		}
		else {
			enemy_arr[i]->set_visible(false);

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
	for (int i = 0; i < 10; i++)
	{
		trash_arr[i]->render();
		enemy_arr[i]->render();

	}
	for (int i = 0; i < 5; i++)
		ally_arr[i]->render();

	destRect.w = 500;
	destRect.h = 500;
	destRect.x = 96;
	destRect.y = 96;
	draw_score(renderer);

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


void GameScreen::draw_score(SDL_Renderer* renderer) {
	std::string number;
	if (score >= 100)
		number = (score % 100) + (score % 10) + '0';
	else
		number = '0' + (score % 100) + (score % 10);
	number = std::to_string(score);
	draw_text(renderer, font_tex,number, 20, 20, 2);

}


void GameScreen::init_enemy_trash(SDL_Renderer* renderer) {
	int checkX, checkY;

	for (int i = 0; i < 10; i++) {
		trash_arr[i] = new Trash(renderer);
		enemy_arr[i] = new Enemy(renderer, surface);

		do {
			checkX = rand() % 924 + 50;
			checkY = rand() % 850 + 50;
			trash_arr[i]->set_x(checkX);
			trash_arr[i]->set_y(checkY);
		} while (is_on_water(checkX + 25, checkY) == false);
		do {
			checkX = rand() % 975 + 75;
			checkY = rand() % 450 + 75;
			enemy_arr[i]->set_x(checkX);
			enemy_arr[i]->set_y(checkY);
		} while (is_on_water(checkX + 25, checkY + 49) == true && is_on_water(checkX, checkY + 49) ==
			true && is_on_water(checkX + 49, checkY + 49) == true);

		trash_arr[i]->loadTexture();
		enemy_arr[i]->loadTexture();

	}
}

void GameScreen:: init_ally(SDL_Renderer* renderer) {
	int checkX, checkY;

	for (int i = 0; i < 5; i++) {
		ally_arr[i] = new Ally(renderer, surface);

		do {
			checkX = rand() % 975 + 75;
			checkY = rand() % 450 + 75;
			ally_arr[i]->set_x(checkX);
			ally_arr[i]->set_y(checkY);
		} while (is_on_water(checkX + 25, checkY + 49) == true && is_on_water(checkX, checkY + 49) ==
			true && is_on_water(checkX + 49, checkY + 49) == true);
		ally_arr[i]->loadTexture();

	}
}


GameScreen::~GameScreen() {
	delete ship;
	delete player;
	SDL_DestroyTexture(font_tex);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(background);
	for (int i = 0; i < 10; i++) {
		delete trash_arr[i];
		delete enemy_arr[i];
	}
}