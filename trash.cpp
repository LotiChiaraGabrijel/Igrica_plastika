#include "trash.h"
Trash::Trash(SDL_Renderer* rend) {
	x = 0;
	y = 0;
	speed = 400;
	texture = nullptr;
	renderer = rend;
	moveX = 0;
	moveY = 0;
}
void Trash::loadTexture() {
	texture = IMG_LoadTexture(renderer, "C:\\Users\\lotig\\Downloads\\Igrica_plastika\\slike\\trash.png");
	destRect.w = 50;
	destRect.h = 50;
	destRect.x = x;
	destRect.y = y;
}

void Trash::update(float deltaTime) {

}

void Trash::render() {
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);

}

Trash::~Trash() {
	if (texture)
		SDL_DestroyTexture(texture);
}
void Trash::set_x(float newX) {
	x = newX;
}
void Trash::set_y(float newY) {
	y = newY;
}
