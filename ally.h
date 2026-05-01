#pragma once
#include <SDL.h>
#include "entity.h"

class Ally :public Entity {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Surface* mask_surface;
	bool xdir, ydir;
	bool alive;


public:
	Ally(SDL_Renderer* rend, SDL_Surface* surface);
	~Ally();
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();
	void change_dir();
	bool get_alive();
	void set_alive(bool x);
};