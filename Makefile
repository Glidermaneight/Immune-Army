all:
	g++ -IC:/random_files/all_things_programming/all_games/src/include -LC:/random_files/all_things_programming/all_games/src/lib -o main main.cpp RenderWindow.cpp Entity.cpp Background.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf