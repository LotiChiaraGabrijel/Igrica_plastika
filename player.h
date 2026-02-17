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
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();
};
