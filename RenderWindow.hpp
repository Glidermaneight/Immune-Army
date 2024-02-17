#pragma once
#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL.h>
#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL_image.h>
#include "Entity.hpp"
#include "Background.hpp"
#include <vector>
#include <string>
class RenderWindow{
public:
	RenderWindow(const char* title, int w, int h);
	SDL_Texture* loadTexture(const char* filepath);
	int getRefreshRate();
	void cleanup();
	void clear();
	void render(Entity& entity);
	SDL_Renderer* get_renderer();
	void display();
	int CAM_X = 2000;
	int CAM_Y = 200;
	SDL_Rect aabb = {640, 320, 74, 74};
	bool render_based_on_pos(const std::vector<std::vector<int>>map, SDL_Texture* red, SDL_Texture* black, SDL_Texture* heart, bool game_over, SDL_Rect& rect);
	int frames = 0;
	SDL_Rect src;
	int i = 0;
	bool completed = false;
	SDL_Rect frame;
	SDL_Rect heart_outline;
private:
	SDL_Rect dst;
	SDL_Rect p_frames[3] = {{0, 0, 16, 16}, {16, 0, 16, 16}, {0, 16, 16, 16}};
	SDL_Window* window;
	SDL_Renderer* renderer;
};