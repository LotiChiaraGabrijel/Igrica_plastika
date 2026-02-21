#pragma once
#include <SDL.h>
#include "entity.h"
class Player : public Entity {
	SDL_Texture* texture;
	SDL_Rect destRect;
	SDL_Renderer* renderer;
	bool on_water;
	SDL_Texture* texture2;
	SDL_Rect destRect2;
public:
	Player(SDL_Renderer* rend);
	~Player();
	float get_x();
	float get_y();
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();
	void set_on_water(bool x);

};
