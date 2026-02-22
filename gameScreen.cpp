#include "gameScreen.h"
#include <iostream>

//gameScreen.cpp
GameScreen::GameScreen(SDL_Renderer* renderer) {
	player = new Player(renderer);
	ship = new Ship(renderer);
	player->loadTexture();  
	ship->loadTexture();
	change = player;
	onWater = false;
	wasOnWater = false;
	surface = IMG_Load("C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\mask.png");
	if (!surface) std::cout << IMG_GetError();
	background = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\background.png");
}
GameScreen::~GameScreen(){
	delete ship;
	delete player;
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(background);
}
bool GameScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	return 1;
}
void GameScreen::update(float deltaTime) {
	change->update(deltaTime);
	Uint8* pixels = (Uint8*)surface->pixels;
	int pitch = surface->pitch;
	int bytesPerPixel = surface->format->BytesPerPixel;
	int checkX = change->get_x() + 50;
	int checkY = change->get_y() + 99;
	if (checkX < 0) checkX = 0;
	else if (checkX > surface->w - 99) checkX = surface->w - 99;
	if (checkY < 0) checkY = 0;
	else if (checkY > surface->h - 99) checkY = surface->h - 99;
	Uint8* pixelAddr = pixels + checkY * pitch + checkX * bytesPerPixel;
	Uint32 pixel = *(Uint32*)pixelAddr;
	Uint8 r, g, b;
	SDL_GetRGB(pixel, surface->format, &r, &g, &b);
	if (r < 50)
		onWater = true;
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
void GameScreen::render(SDL_Renderer* renderer) {
	
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;
	SDL_RenderCopy(renderer, background, nullptr, &destRect);
	//player->render();
	change->render();
}