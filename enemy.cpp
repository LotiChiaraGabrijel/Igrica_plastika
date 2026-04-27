#include "enemy.h"
#include <iostream>
Enemy::Enemy(SDL_Renderer* rend, SDL_Surface* surface) {
	x = 0;
	y = 0;
	speed = 60;
	texture = nullptr;
	renderer = rend;
	destRect.w = 50;
	destRect.h = 50;
	destRect.y = y;
	destRect.x = x;
	visible = false;
	alive = true;
	together = false;
	xdir = 1;
	ydir = 1;
	this->mask_surface = surface;
}

void Enemy::loadTexture() {
	texture = IMG_LoadTexture(renderer, "slike/enemy.png");

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
	if (alive == true && visible == true) {
		destRect.x = x;
		destRect.y = y;
		SDL_RenderCopy(renderer, texture, nullptr, &destRect);
	}
}
void Enemy::set_together(bool x) {
	together = x;
}
bool Enemy::get_together() {
	return together;
}


void Enemy::change_dir() {
	ydir = !ydir;
	xdir = !xdir;
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


bool Enemy::is_in_radius(SDL_Rect rect) {
	int playerCenterX = rect.x + rect.w / 2;
	int playerCenterY = rect.y + rect.h / 2;

	int enemyCenterX = (int)x + destRect.w / 2;
	int enemyCenterY = (int)y + destRect.h / 2;

	int dx = enemyCenterX - playerCenterX;
	int dy = enemyCenterY - playerCenterY;

	int radius = 200;

	return dx * dx + dy * dy <= radius * radius;
}

void Enemy::set_visible(bool x) {
	visible = x;

}
