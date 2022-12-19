#include <iostream>
#include"include/Game.h"
#include <SDL2/SDL.h>

int main(int argc, char* args[]) 
{
	Game game;
	bool isSuccess = game.Initialize();

	if (isSuccess) {
		game.RunLoop();
	}

	game.ShutDown();

	std::cin.get();
	return 0;
}
