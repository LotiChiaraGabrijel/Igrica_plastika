#include "gameScreen.h"
//gameScreen.cpp
GameScreen::GameScreen(SDL_Renderer* renderer) {
	player = new Player(renderer);
	player->loadTexture();  
}
GameScreen::~GameScreen(){
	delete player;
}
bool GameScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
}
void GameScreen::update(float deltaTime) {
	player->update(deltaTime);

}
void GameScreen::render(SDL_Renderer* renderer) {
	player->render();

}