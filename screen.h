#pragma once
#include <SDL.h>
class Screen {
public:
	virtual bool handleEvents(SDL_Event& e) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual ~Screen() = default;

};