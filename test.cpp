#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL.h>
#include <C:\random_files\all_things_programming\all_games\src\include\SDL2\SDL_image.h>
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
		return 1;
    }

  // Initialize images
    if (!(IMG_Init(IMG_INIT_PNG))){
	    std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	    return 1;
    }
	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
	if(!window){
		std::cout << "Couldn't create window. " << SDL_GetError() << std::endl;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* bullet = IMG_LoadTexture(renderer, "C:/random_files/all_things_programming/all_games/images/Bullet.png");
	if(!bullet){
		std::cout << "Couldn't load the image. " << SDL_GetError() << std::endl;
	}
	SDL_Rect dst = {50, 50, 256, 256};
	bool gameon = true;
	while(gameon){
		SDL_RenderPresent(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, bullet, NULL, &dst);
	}
    return 0;
}
