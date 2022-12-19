#include <iostream>
#include <SDL2/SDL.h>

#include"include/Game.h"

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
