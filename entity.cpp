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