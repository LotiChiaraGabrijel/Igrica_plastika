#include "ship.h"

Ship::Ship(SDL_Renderer* rend){
	x = 0;
	y = 0;
	speed = 400;
	texture = nullptr;
	renderer = rend;
}
void Ship::loadTexture() {
	texture = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\ship_img.png");
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

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x > 1024 - 100) x = 1024 - 100;
	if (y > 900 - 100) y = 900 - 100;
}
Ship::~Ship() {
	if (texture)
		SDL_DestroyTexture(texture);
}

float Ship::get_x() {
	return x;
}
float Ship::get_y() {
	return y;
}
void Ship::set_x(float newX) {
	x = newX;
}
void Ship::set_y(float newY) {
	y = newY;
}