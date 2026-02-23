#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include "entity.h"
#include <cstdlib>

class Trash : public Entity {

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect destRect;
	float moveX,
		moveY;
public:
	Trash(SDL_Renderer* rend);
	~Trash();
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();
	void set_x(float newX) override;
	void set_y(float newY) override;
};