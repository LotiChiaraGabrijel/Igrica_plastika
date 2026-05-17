#include "trash.h"
Trash::Trash(SDL_Renderer* rend) {
	x = 0;
	y = 0;
	speed = 50;
	texture = nullptr;
	renderer = rend;
	alive = true;
	xdir = 1;
	ydir = 1;
}
void Trash::loadTexture() {
	if (rand() % 2 == 0)
		texture = IMG_LoadTexture(renderer, "slike/trash.png");
	else
		texture = IMG_LoadTexture(renderer, "slike/trash2.png");

	destRect.w = 50;
	destRect.h = 50;
	destRect.x = x;
	destRect.y = y;
}

void Trash::update(float deltaTime) {
	int dir = rand() % 1000;
	if (dir == 1) xdir = !xdir;
	dir = rand() % 1000;
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
	if (y > 825) y = 825;

}

void Trash::render() {
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);

}

Trash::~Trash() {
	if (texture)
		SDL_DestroyTexture(texture);


}


void Trash::change_dir() {
	ydir = !ydir;
}
