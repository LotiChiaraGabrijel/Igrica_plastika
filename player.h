#pragma once
#include <SDL.h>
#include "entity.h"
class Player : public Entity {
	SDL_Texture* texture;
	SDL_Rect destRect;
	SDL_Renderer* renderer;


public:
	Player(SDL_Renderer* rend);
	~Player();
	float get_x() override;
	float get_y() override;
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();
	void set_x(float newX) override;
	void set_y(float newY) override;

};
