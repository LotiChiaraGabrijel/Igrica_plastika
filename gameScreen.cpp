#include "gameScreen.h"

//gameScreen.cpp
GameScreen::GameScreen(SDL_Renderer* renderer) {
	player = new Player(renderer);
	player->loadTexture();  
	surface = IMG_Load("C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\mask.png");
	background = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\background.png");

}
GameScreen::~GameScreen(){

	delete player;
}
bool GameScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
}
void GameScreen::update(float deltaTime) {
	player->update(deltaTime);
	Uint8* pixels = (Uint8*)surface->pixels;
	int pitch = surface->pitch;
	int bytesPerPixel = surface->format->BytesPerPixel;
	int checkX = player->get_x() + 50;
	int checkY = player->get_y() + 99;
	Uint8* pixelAddr = pixels + checkY * pitch + checkX * bytesPerPixel;
	Uint32 pixel = *(Uint32*)pixelAddr;
	Uint8 r, g, b;
	SDL_GetRGB(pixel, surface->format, &r, &g, &b);
	if (r < 50)
		player->set_on_water(true);
	else
		player->set_on_water(false);

	

}
void GameScreen::render(SDL_Renderer* renderer) {
	
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;
	SDL_RenderCopy(renderer, background, nullptr, &destRect);
	player->render();
}