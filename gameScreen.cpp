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
		int checkX, checkY;
		do
		{
			checkX = rand() % 975 + 50;
			checkY = rand() % 850 + 50;
			trash_arr[i]->set_x(checkX);
			trash_arr[i]->set_y(checkY);
		} while (is_on_water(checkX, checkY) == false);
		trash_arr[i]->loadTexture();
	}
	

}
GameScreen::~GameScreen(){
	delete ship;
	delete player;
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(background);
	for (int i = 0; i < 10; i++) {
		delete trash_arr[i];
	}
}
bool GameScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	return 1;
}
void GameScreen::update(float deltaTime) {
	change->update(deltaTime);

	int checkX = change->get_x() + 50;
	int checkY = change->get_y() + 99;

	if (is_on_water(checkX, checkY))
	{
		onWater = true;
		for (int i = 0; i < 10; i++) 
			if (check_collision(trash_arr[i]->get_rect(), change->get_rect()))
				trash_arr[i]->set_alive(false);
		

	}
	else
		onWater = false;

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
				

	

	


bool GameScreen::is_on_water(int x, int y) {
	if (x < 0) x = 0;
	else if (x > surface->w - 99) x = surface->w - 99;
	if (y < 0) y = 0;
	else if (y > surface->h - 99) y = surface->h - 99;
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
		trash_arr[i]->render();
}

bool GameScreen::check_collision(SDL_Rect a, SDL_Rect b) {
	if (a.x + a.w/2 <= b.x) return false;
	if (a.x >= b.x + b.w / 2) return false;
	if (a.y + a.h / 2 <= b.y) return false;
	if (a.y >= b.y + b.h / 2) return false;
	return true;
} 
