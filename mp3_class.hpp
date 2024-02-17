#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL_mixer.h>
#include <iostream>
#pragma once
class Music{
	public:
		Mix_Music* return_noise(){
			return sound;
		}
		Music(const char* mus){
			sound = Mix_LoadMUS(mus);
			if(sound == NULL){
				std::cout << "Couldn't load whoosh. Error: %s\n" << std::endl;
			}
		}
		void play(){
			Mix_PlayMusic(sound, 0);
		}
		void die(){
			Mix_FreeMusic(sound);
		}
	private:
		Mix_Music* sound;
};