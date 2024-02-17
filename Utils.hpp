#pragma once

#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL.h>

namespace utils{

	inline float hireTimeinSeconds(){
		float t = SDL_GetTicks();
		t *= 0.001f;
		return t;
	}

}