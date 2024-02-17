#pragma once
#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL.h>
#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL_image.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <future>
#include <cmath>
#include <iostream>
#include "mp3_class.hpp"
class Virus1;
class Enemy;
class Entity{
public:
	Entity(float X, float Y, SDL_Texture* tex);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	float X, Y;
	float rotation;
	SDL_RendererFlip flip;
	int return_health();
	void set_health();
	void set_tex(SDL_Texture* tex);
private:
	bool attack;
	SDL_Rect currentFrame;
	SDL_Texture* TEX;
	int health = 3;
};
Uint32 boom_delay(Uint32 interval, void* param);
class Bullet{
	public:
		Bullet(float X, float Y, SDL_Texture* tex) : X(bullet_rect.x), Y(bullet_rect.y), bullet_tex(bullet_tex){
			bullet_rect.x = 640;
			bullet_rect.y = 350;
			bullet_rect.w = 256;
			bullet_rect.h = 256;
		}
		float X, Y;
		void fly(Entity& entity){
			SDL_Rect entity_rect = entity.getCurrentFrame();
			bullet_rect.y = 320 + (entity_rect.h / 2);
			bullet_rect.x = 640 + (entity_rect.w / 2);
			bullet_rect.y += 0;
			bullet_rect.x += 10;
			std::cout << bullet_rect.x << std::endl;
			std::cout << bullet_rect.y << std::endl;
			/*
			float angle = entity.rotation * 3.14 / 180.0;
			float delta_x = 5 * std::cos(angle);
			float delta_y = 5 * std::sin(angle);
			bullet_rect.x += delta_x;
			bullet_rect.y += delta_y;
			*/
		}
		void render_self(SDL_Renderer* renderer){
			SDL_Rect dst;
			dst.x = bullet_rect.x;
			dst.y = bullet_rect.y;
			dst.w = bullet_rect.w;
			dst.h = bullet_rect.h;
			SDL_RenderCopy(renderer, get_bullet_tex(), NULL, &dst);
		}
		SDL_Texture* get_bullet_tex(){
			return bullet_tex;
		}
		SDL_Rect& get_bullet_rect(){
			return bullet_rect;
		}
		void set_rotation(int Rotation){
			rotation = Rotation;
		}
		int get_rotation(){
			return rotation;
		}
	private:
		SDL_Rect bullet_rect;
		SDL_Texture* bullet_tex;
		SDL_RendererFlip flip;
		int rotation;
};
void move_to_screen(SDL_Renderer* renderer);
class Enemy{
	public:
		Enemy(float X, float Y, SDL_Texture* tex);
		float X, Y;
		SDL_Rect& get_enemy_rect();
		SDL_Texture* get_enemy_tex();
		bool death();
		void yes();
		float get_rotation();
		void set_rotation(float Rotation);
		SDL_RendererFlip enemy_flip;
		void no();
		bool get_live();
		void set_health();
		Uint32 start_time = SDL_GetTicks();
		void render_self(SDL_Renderer* renderer);
		void game_over(bool game_over);
		bool return_alive();
		void dead();
	protected:
		float rotation;
		bool can_live = false;
		bool alive = true;
		SDL_Texture* TEX;
		SDL_Rect enemy_rect;
		int x, y = 0;
		bool should_move = false;
};
class Virus1 : public Enemy{
	public:
		Virus1(float X, float Y, SDL_Texture* tex) : Enemy(X, Y, tex){
			enemy_rect.x = x + 120;
			enemy_rect.y = y + 320;
			enemy_rect.w = 256;
			enemy_rect.h = 256;
		}
		void live(Entity& entity, SDL_Renderer* renderer, SDL_Rect frame, const Uint8* state){
			SDL_Rect entity_rect = entity.getCurrentFrame();
			float angle = std::atan2(entity_rect.x, entity_rect.y);
			float actual_angle = angle * 180.0f / 3.14;
			set_rotation(actual_angle);
			render_self(renderer);
			if(!SDL_HasIntersection(&enemy_rect, &frame)){
				enemy_rect.x += 2;
			}else{
				enemy_rect.x += 10;
			}
			state = SDL_GetKeyboardState(NULL);
			if(state[SDL_SCANCODE_S]){
				should_move = true;
				if(should_move){
					enemy_rect.y += 1;
					should_move = false;
				}
			}
			if(state[SDL_SCANCODE_W]){
				should_move = true;
				if(should_move){
					enemy_rect.y -= 1;
					should_move = false;
				}
			}
		}
};