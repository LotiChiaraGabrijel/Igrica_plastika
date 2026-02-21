#include "player.h"
#include <SDL_image.h>
#include <ctime>
#include < cstdlib >
Player::Player(SDL_Renderer* rend) {
	x = rand() % -1025 ;
	y = rand() % -900;
	speed = 400;
	texture = nullptr;
	texture2 = nullptr;
	renderer = rend;
	on_water = true;
}
Player::~Player() {
	if (texture)
		SDL_DestroyTexture(texture);
}

void Player::loadTexture() {
	texture2 = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\player_beach.png");
	texture = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\ship_img.png");

	destRect.w = 100;
	destRect.h = 100;
	destRect.x = x;
	destRect.y = y;

	destRect2.w = 100;
	destRect2.h = 100;
	destRect2.x = x;
	destRect2.y = y;
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
	if (x > 1024-100) x = 1024-100;
	if (y > 900-100) y = 900-100;
}
void Player::render() {

	if (on_water == true)
	{
		destRect.x = x;
		destRect.y = y;
		SDL_RenderCopy(renderer, texture, nullptr, &destRect);
	}
	else
	{
		destRect2.x = x;
		destRect2.y = y;
		SDL_RenderCopy(renderer, texture2, nullptr, &destRect2);
	}

}

float Player::get_x() {
	return x;
}
float Player::get_y() {
	return y;
}
void Player::set_on_water(bool x) {
	on_water = x;
}
