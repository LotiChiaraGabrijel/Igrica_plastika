#pragma once
#include <SDL.h>
class Entity {
protected:
	SDL_Rect destRect;
public: 
	Entity();
	float x, y, speed;
	void move();
	virtual void update(float deltaTime);
	virtual void render();
	float get_x();
	float get_y();
	void set_x(float newX);
	void set_y(float newY);
	SDL_Rect get_rect();
	bool check_collision(SDL_Rect a);

};