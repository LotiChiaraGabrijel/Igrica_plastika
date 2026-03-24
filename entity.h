#pragma once
#include <SDL.h>
class Entity {
	SDL_Rect destRect;
	bool alive;
	
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

};
