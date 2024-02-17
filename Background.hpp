#pragma once
#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL.h>
#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL_image.h>
class Background{
public:
	Background(float X, float Y, SDL_Texture* cant_see);
	SDL_Rect get_tile();
	float getX();
	float getY();
	SDL_Texture* color_black();
	float X, Y;
	SDL_Texture* cant_see;
private:
	SDL_Rect tile;
	SDL_Texture* invisible_tile;
	float x, y;
};