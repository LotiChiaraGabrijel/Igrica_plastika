#pragma once
#include <SDL.h>
class Entity {

	bool alive;
public: 
	Entity();
	float x, y, speed;
	void move();
	virtual void update(float deltaTime);
	virtual void render();
};