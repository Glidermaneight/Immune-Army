#include "Entity.hpp"
#include "RenderWindow.hpp"
int i = 0;
Entity::Entity(float x, float y, SDL_Texture* tex):X(currentFrame.x), Y(currentFrame.y), TEX(tex){
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 256;
	currentFrame.h = 256;
}
SDL_Texture* Entity::getTex(){
	return TEX;
}
SDL_Rect Entity::getCurrentFrame(){
	return currentFrame;
}
void Entity::set_health(){
	health--;
}
void Entity::set_tex(SDL_Texture* tex) {
    TEX = tex;
}
Uint32 boom_delay(Uint32 interval, void* param){
	i++;
	return interval;
}
Enemy::Enemy(float X, float Y, SDL_Texture* tex):X(enemy_rect.x), Y(enemy_rect.y), TEX(tex){
	enemy_rect.x = 0;
	enemy_rect.y = 0;
	enemy_rect.w = 256;
	enemy_rect.h = 256;
}
SDL_Rect& Enemy::get_enemy_rect(){
	return enemy_rect;
}
SDL_Texture* Enemy::get_enemy_tex(){
	return TEX;
}
void Enemy::yes(){
	can_live = true;
	alive = true;
}
void Enemy::no(){
	can_live = false;
	alive = false;
}
bool Enemy::get_live(){
	return can_live;
}
float Enemy::get_rotation(){
	return rotation;
}
void Enemy::set_rotation(float Rotation){
	rotation = 360.f - Rotation;
}
void Enemy::render_self(SDL_Renderer* renderer){
	SDL_Rect dst;
	dst.x = enemy_rect.x;
	dst.y = enemy_rect.y;
	dst.w = enemy_rect.w / 3.5;
	dst.h = enemy_rect.h / 3.5;
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderCopyEx(renderer, get_enemy_tex(), NULL, &dst, get_rotation(), NULL, enemy_flip);
}
void Enemy::game_over(bool game_over){
	game_over = true;
}
bool Enemy::return_alive(){
	return alive;
}
void Enemy::dead(){
	alive = false;
}