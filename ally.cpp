#include "ally.h"
#include <iostream>
#include <SDL_image.h>

Ally::Ally(SDL_Renderer* rend, SDL_Surface* surface) {
	x = 0;
	y = 0;
	speed = 60;
	texture = nullptr;
	renderer = rend;
	destRect.w = 50;
	destRect.h = 50;
	destRect.y = y;
	destRect.x = x;
	xdir = 1;
	ydir = 1;
	alive = true;
	this->mask_surface = surface;
}

void Ally::loadTexture() {
	texture = IMG_LoadTexture(renderer, "slike/ally.png");
}
void Ally::change_dir() {
	ydir = !ydir;
}
bool Ally::get_alive() {
	return alive;
}
void Ally::set_alive(bool x){
	alive = x;
}

void Ally::update(float deltaTime) {
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

void Ally::render() {
	if (alive == true){
		destRect.x = x;
		destRect.y = y;
		SDL_RenderCopy(renderer, texture, nullptr, &destRect);
	}

}

Ally::~Ally() {
	if (texture)
		SDL_DestroyTexture(texture);
}


