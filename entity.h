#pragma once
#include <SDL.h>
class Entity {

	bool alive;
public: 
	Entity();
	int x, y, speed;
	void move();
	virtual void update();
	virtual void render();
};