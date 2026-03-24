#include "entity.h"
Entity::Entity() {
}
void Entity::move() {

}
void Entity::update(float deltaTime) {

}
void Entity::render() {

}
float Entity::get_x() {
	return x;
}
float Entity::get_y() {
	return y;
}
void Entity::set_x(float newX) {
	x = newX;
}

void Entity::set_y(float newY) {
	y = newY;
}
SDL_Rect Entity::get_rect() {
	return destRect;
}



bool Entity::check_collision(SDL_Rect a) {
	if (destRect.x + destRect.w / 2 <= a.x) return false;
	if (destRect.x >= a.x + a.w / 2) return false;
	if (destRect.y + destRect.h / 2 <= a.y) return false;
	if (destRect.y >= a.y + a.h / 2) return false;
	return true;
}
