#include "Background.hpp"
#include "Entity.hpp"
Background::Background(float x, float y, SDL_Texture* invisible_tile) :X(x), Y(y), invisible_tile(cant_see){
	tile.x = 0;
	tile.y = 0;
	tile.w = 256;
	tile.h = 256;
}
SDL_Rect Background::get_tile(){
	return tile;
}
SDL_Texture* Background::color_black(){
	return invisible_tile;
}
float Background::getX(){
	return x;
}
float Background::getY(){
	return y;
}