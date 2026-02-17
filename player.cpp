#include "player.h"
#include <SDL_image.h>
Player::Player(SDL_Renderer* rend) {
	x = 500;
	y = 400;
	speed = 400;
	texture = nullptr;
	renderer = rend;
}
Player::~Player() {
	if (texture)
		SDL_DestroyTexture(texture);
}

void Player::loadTexture() {
	texture = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\ship_img.png");
	destRect.w = 100;
	destRect.h = 100;
	destRect.x = x;
	destRect.y = y;
}
void Player::update(float deltaTime) {
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
	if (x > 1000) x = 1000;
	if (y > 1000) y = 1000;
}
void Player::render() {
	destRect.x = x; 
	destRect.y = y;
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}