#include "enemy.h"

Enemy::Enemy(SDL_Renderer* rend, SDL_Surface* surface) {
	x = 0;
	y = 0;
	speed = 400;
	texture = nullptr;
	renderer = rend;
	destRect.w = 50;
	destRect.h = 50;
	destRect.y = y;
	destRect.x = x;
	alive = true;
	this->mask_surface = surface;
}

void Enemy::loadTexture() {
	texture = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\enemy.png");


}

void Enemy::update(float deltaTime) {

}

void Enemy::render() {
	if (alive == true)
		SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}


Enemy::~Enemy() {
	if (texture)
		SDL_DestroyTexture(texture);
}
