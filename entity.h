#pragma once
#include <SDL.h>
class Entity {
	SDL_Rect destRect;
public: 
	Entity();
	float x, y, speed;
	void move();
	virtual void update(float deltaTime);
	virtual void render();
	float get_x();
	float get_y();
	virtual void set_x(float newX);
	virtual void set_y(float newY);
	virtual SDL_Rect get_rect();
	bool check_collision(SDL_Rect a);

};