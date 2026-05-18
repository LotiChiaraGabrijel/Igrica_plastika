#pragma once
#include "entity.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>

class Enemy : public Entity {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Surface* mask_surface;
	bool alive;
	bool together;

	bool xdir, ydir;
	bool visible;
	bool following;
public:
	Enemy(SDL_Renderer* rend, SDL_Surface* surface);
	~Enemy();
	void update(float deltaTime) override;
	void render() override;
	void loadTexture();
	void change_dir();
	bool is_in_radius(SDL_Rect rect);
	void set_visible(bool x);
	void set_together(bool x);
	bool get_together();
	void follow(float a, float b, float deltaTime);
	bool get_follow();
};