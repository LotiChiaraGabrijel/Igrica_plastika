#pragma once
#include "entity.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>

class Enemy : public Entity {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect destRect;
	SDL_Surface* mask_surface;
	bool alive;
	bool xdir, ydir;
	bool visible;

public:
	Enemy(SDL_Renderer* rend, SDL_Surface* surface);
	~Enemy();
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();
	void change_dir();
	void set_alive(bool x);
	bool get_alive();
	bool is_in_radius(SDL_Rect rect);
	void set_visible(bool x);
};