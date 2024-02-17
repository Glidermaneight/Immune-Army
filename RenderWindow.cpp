#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Background.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
RenderWindow::RenderWindow(const char* title, int w, int h) // this function initializes a window
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if(window == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
		
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
SDL_Texture* RenderWindow::loadTexture(const char* filepath){ // This function loads a texture, which can be drawn to the window
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filepath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}
int RenderWindow::getRefreshRate(){
	int display_index = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(display_index, 0, &mode);
	return mode.refresh_rate;
}
void RenderWindow::cleanup(){ // This function destroys the window
	SDL_DestroyWindow(window);
}

void RenderWindow::clear(){ // This function clears the renderer
	SDL_RenderClear(renderer);
}
void RenderWindow::render(Entity& entity){ // This function renders the aforementioned texture to the window
	src.x = p_frames[i].x;
	src.y = p_frames[i].y;
	src.w = 16;
	src.h = 16;
	dst.x = entity.getCurrentFrame().x + 640;
	dst.y = entity.getCurrentFrame().y + 320;
	dst.w = entity.getCurrentFrame().w / 3.5;
	dst.h = entity.getCurrentFrame().h / 3.5;
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderCopyEx(renderer, entity.getTex(), &src, &dst, entity.rotation, NULL, entity.flip);
}
void RenderWindow::display(){
	SDL_RenderPresent(renderer);
	frames++;
}
SDL_Renderer* RenderWindow::get_renderer(){
	return renderer;
}
bool RenderWindow::render_based_on_pos(const std::vector<std::vector<int>> map, SDL_Texture* red, SDL_Texture* black, SDL_Texture* heart, bool game_over, SDL_Rect& rect){
	bool collision = false;
	frame = {0, 0, 0, 0};
	heart_outline = { 0, 0, 0, 0 };
	auto IntersectRect = [&]{
    return !(aabb.x + 5 >= (frame.x + frame.w) || 
             (aabb.x + aabb.w) - 5 <= frame.x || 
             aabb.y + 5 >= (frame.y + frame.h) || 
             (aabb.y + aabb.h) - 5 <= frame.y);
	};
	auto player_collide = [&]{
		return !(rect.x + 5 >= (frame.x + frame.w) ||
				(rect.x + rect.w) - 5 <= frame.x ||
				rect.y + 5 >= (frame.y + frame.h) ||
				(aabb.y + aabb.h) - 5 <= frame.y);
	};
	auto return_dist = [&](int x_1, int x_2, int y_1, int y_2){
		return std::sqrt(std::pow(x_2 - x_1, 2) + std::pow(y_2 - y_1, 2));
	};
	for(int y = CAM_Y / 74; y < (CAM_Y + 720 + 74) / 74; ++y){
		for(int x = CAM_X / 74; x < (CAM_X + 1280 + 74) / 74; ++x){
			if(y < map.size() && x < map[y].size()){
				const Uint8* state = SDL_GetKeyboardState(NULL);
				int tile = map[y][x];
				frame = {x * 74 - CAM_X, y * 74 - CAM_Y, 74, 74};
				heart_outline = { x * 74 - CAM_X, y * 74 - CAM_Y, 74, 74 };
				if(tile == 1){
					SDL_RenderCopy(renderer, red, NULL, &frame);
					if(IntersectRect() || player_collide())
						collision = true;
				}
				if(tile == 0){
					SDL_RenderCopy(renderer, black, NULL, &frame);
					int l_dist = return_dist(aabb.x, (frame.x + frame.w), aabb.y, frame.y);
					int r_dist = return_dist((aabb.x + aabb.w), frame.x, aabb.y, frame.y);
					int u_dist = return_dist(aabb.x, frame.x, aabb.y, (frame.y + frame.h));
					int b_dist = return_dist(aabb.x, frame.x, (aabb.y + aabb.h), frame.y);
					if ((r_dist <= 10) || (b_dist <= 10) || (u_dist <= 10) || (l_dist <= 10)){
						collision = false;
					}if(IntersectRect() || player_collide()){
						collision = false;
					}
				}
				if(tile == 3){
					SDL_RenderCopy(renderer, heart, NULL, &frame);
					if(IntersectRect() || player_collide()){
						collision = false;
					}
				}
				if(tile == 4){
					SDL_RenderCopy(renderer, black, NULL, &heart_outline);
					if(SDL_HasIntersection(&rect, &heart_outline) || SDL_HasIntersection(&aabb, &heart_outline)){
						collision = false;
					}
				}
				if(CAM_X <= 1800 && CAM_Y >= 270 && CAM_Y <= 330 && (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_Z])){
					collision = false;
				}
				if(CAM_X <= 1800 && CAM_Y >= 505 && CAM_Y <= 565 && (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_Z])){
					collision = false;
				}
				if(CAM_X >= 2620 && CAM_Y >= 280 && CAM_Y <= 330 && (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_E] || state[SDL_SCANCODE_C])){
					collision = false;
				}
				if(CAM_X >= 2620 && CAM_Y >= 510 && CAM_Y <= 560 && (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_E] || state[SDL_SCANCODE_C])){
					collision = false;
				}
				if((CAM_X <= 1785 && CAM_Y >= 480 && CAM_Y <= 490 && (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_Z] || state[SDL_SCANCODE_C]))){
					collision = false;
				}
				if(CAM_X >= 2635 && CAM_Y <= 790 && CAM_Y >= 770 && (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_E])){
					collision = false;
				}
				if(CAM_X >= 2640 && CAM_Y <= 1015 && CAM_Y >= 1005 && (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_Z] || state[SDL_SCANCODE_C])){
					collision = false;
				}
				if((CAM_X >= 2640 && CAM_Y <= 370 && CAM_Y >= 350 && (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_E])) || (CAM_X >= 2640 && CAM_Y <= 490 && CAM_Y >= 480 && (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_Z] || state[SDL_SCANCODE_C]))){
					collision = false;
				}
				if((CAM_X <= 1780 && CAM_Y >= 360 && CAM_Y <= 370 && (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_E])) || (CAM_X <= 1780 && CAM_Y >= 480 && CAM_Y <= 490 && (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_Z] || state[SDL_SCANCODE_C]))){
					collision = false;
				}
				if((CAM_X >= 2620 && CAM_Y >= 705 && CAM_Y <= 770 && (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_E] || state[SDL_SCANCODE_C])) || (CAM_X >= 2635 && CAM_Y >= 760 && CAM_Y <= 705 && (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_E]))){
					collision = false;
				}
				if(CAM_X >= 2620 && CAM_Y >= 1020 && CAM_Y <= 1080 && (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_E] || state[SDL_SCANCODE_C])){
					collision = false;
				}
				if((CAM_X <= 1760 && CAM_Y <= 790 && CAM_Y >= 785  && (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_E])) || (CAM_X <= 1765 && CAM_Y >= 1010 && CAM_Y <= 1015 && (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_Z] || state[SDL_SCANCODE_C]))){
					collision = false;
				}
				if((CAM_X <= 1790 && CAM_Y <= 1080 && CAM_Y >= 1040 && (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_Z])) || (CAM_X <= 1800 && CAM_Y >= 710 && CAM_Y <= 775 && (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_Z]))){
					collision = false;
				}
				if(CAM_X <= 2540 && CAM_X >= 2500 && CAM_Y >= 740 && CAM_Y <= 1000 && (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_Z])){
					collision = false;
				}
				if(CAM_Y <= 50 && (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_E] || state[SDL_SCANCODE_Q])){
					collision = false;
				}
			}else{
				std::cout << "Out of bounds error" << std::endl;
				CAM_X = 2000;
				CAM_Y = 200;
			}
		}
	}
	SDL_RenderDrawRect(renderer, &aabb);
	return collision;
}