#include "ship.h"

Ship::Ship(SDL_Renderer* rend){
	x = 0;
	y = 0;
	speed = 400;
	texture = nullptr;
	renderer = rend;
}
void Ship::loadTexture() {
	texture = IMG_LoadTexture(renderer, "slike/ship_img.png");
	destRect.w = 100;
	destRect.h = 100;
	destRect.x = x;
	destRect.y = y;
}

void Ship::render() {
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void Ship::update(float deltaTime) {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W])
		y -= speed * deltaTime;

	if (state[SDL_SCANCODE_S])
		y += speed * deltaTime;

	if (state[SDL_SCANCODE_A])
		x -= speed * deltaTime;

	if (state[SDL_SCANCODE_D])
		x += speed * deltaTime;

	if (x < -25) x = -25;
	if (x > 950) x = 950;
	if (y > 825) y = 825;
}
Ship::~Ship() {
	if (texture)
		SDL_DestroyTexture(texture);
}


