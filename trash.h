#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include "entity.h"
#include <cstdlib>

class Trash : public Entity {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	bool alive;
	bool xdir, ydir;
public:
	Trash(SDL_Renderer* rend);
	~Trash();
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();
	void change_dir();
	bool get_alive();

	void set_alive(bool x);

};