#include "player.h"
#include <SDL_image.h>
Player::Player(SDL_Renderer* rend) {
	x = 500;
	y = 400;
	speed = 4;
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
void Player::update() {
}
void Player::render() {
	destRect.x = x; 
	destRect.y = y;
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}