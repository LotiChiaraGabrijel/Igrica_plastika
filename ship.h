#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include "entity.h"
#include <cstdlib>


class Ship : public Entity {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect destRect;
public:
	Ship(SDL_Renderer* rend);
	~Ship();
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();

	void set_x(float newX) override;
	void set_y(float newY) override;
	SDL_Rect get_rect() override;

};

