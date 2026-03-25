#include "enemy.h"
#include <iostream>
Enemy::Enemy(SDL_Renderer* rend, SDL_Surface* surface) {
	x = 0;
	y = 0;
	speed = 100;
	texture = nullptr;
	renderer = rend;
	destRect.w = 50;
	destRect.h = 50;
	destRect.y = y;
	destRect.x = x;
	alive = true;
	xdir = 1;
	ydir = 1;
	this->mask_surface = surface;
}

void Enemy::loadTexture() {
	texture = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\enemy.png");


}

void Enemy::update(float deltaTime) {
	int dir = rand() % 600;
	if (dir == 1) xdir = !xdir;
	dir = rand() % 600;
	if (dir == 1) ydir = !ydir;
	if (xdir == 1)
		x += deltaTime * speed;
	else
		x -= deltaTime * speed;
	if (ydir == 1)
		y += deltaTime * speed;
	else
		y -= deltaTime * speed;

	if (x < -25) x = -25;
	if (x > 950) x = 950;
	if (y < 0) y = 0;
}

void Enemy::render() {
	if (alive == true) {
		destRect.x = x;
		destRect.y = y;
		SDL_RenderCopy(renderer, texture, nullptr, &destRect);
	}
}



void Enemy::change_dir() {
	ydir = !ydir;
}

void Enemy::set_alive(bool x) {
	alive = x;
}

Enemy::~Enemy() {
	if (texture)
		SDL_DestroyTexture(texture);
}

bool Enemy::get_alive() {
	return alive;
}
