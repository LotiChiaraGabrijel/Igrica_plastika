#pragma once
#include <SDL.h>
class Entity {
	int x, y, speed;
	bool alive;
public: 
	Entity();
	void move();
	void update();
	void render();
};