#include "gameScreen.h"
#include <iostream>

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
	surface = IMG_Load("C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\mask.png");
	if (!surface) std::cout << IMG_GetError();
	background = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\background.png");
	for (int i = 0; i < 10; i++) {
		trash_arr[i] = new Trash(renderer);
		enemy_arr[i] = new Enemy(renderer, surface);
		int checkX, checkY;
		do {
			checkX = rand() % 924 + 50;
			checkY = rand() % 850 + 50;
			trash_arr[i]->set_x(checkX);
			trash_arr[i]->set_y(checkY);
		} while (is_on_water(checkX+25, checkY) == false);
		do {
			checkX = rand() % 975 + 50;
			checkY = rand() % 450 + 50;
			enemy_arr[i]->set_x(checkX);
			enemy_arr[i]->set_y(checkY);
		} while (is_on_water(checkX+25, checkY+ 49) == true || is_on_water(checkX, checkY + 49) ==
			true || is_on_water(checkX + 49, checkY + 49) == true
			|| is_on_water(checkX + 25, checkY + 25));
		trash_arr[i]->loadTexture();
		enemy_arr[i]->loadTexture();
	}


}

bool GameScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	return 1;
}

void GameScreen::update(float deltaTime) {
	int checkX, checkY;
	change->update(deltaTime);
	for (int i = 0; i < 10; i++) {
		float oldX = enemy_arr[i]->get_x(),
		oldY = enemy_arr[i]->get_y();
		enemy_arr[i]->update(deltaTime);

		checkX = enemy_arr[i]->get_x();
		checkY = enemy_arr[i]->get_y();
		if (is_on_water(checkX + 25, checkY + 49) == true || is_on_water(checkX, checkY + 49) ==
			true || is_on_water(checkX + 49, checkY + 49) == true
			|| is_on_water(checkX + 25, checkY + 25) || is_on_water(checkX + 49, checkY + 25)
			|| is_on_water(checkX, checkY + 25)
			|| is_on_water(checkX + 49, checkY) || is_on_water(checkX, checkY) 
			|| is_on_water(checkX + 25, checkY)) {
			enemy_arr[i]->set_x(oldX);
			enemy_arr[i]->set_y(oldY);
			enemy_arr[i]->change_dir();
		}
		

	}
	checkX = change->get_x() + 50;
	checkY = change->get_y() + 99;

	if (is_on_water(checkX, checkY)) {
		onWater = true;
		for (int i = 0; i < 10; i++)
		{
			if (change->check_collision(trash_arr[i]->get_rect()))
				trash_arr[i]->set_alive(false);
		}
	}
	else
		onWater = false;

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







bool GameScreen::is_on_water(int x, int y) {
	if (x < 0) x = 0;
	else if (x > surface->w-1) x = surface->w-1;
	if (y < 0) y = 0;
	else if (y > surface->h-1) y = surface->h-1;
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
}
GameScreen::~GameScreen() {
	delete ship;
	delete player;
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(background);
	for (int i = 0; i < 10; i++) {
		delete trash_arr[i];
		delete enemy_arr[i];
	}
}