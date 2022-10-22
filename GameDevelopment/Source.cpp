#include <iostream>
#include <include/Game.h>

int main(int argc, char* args[]) 
{
	Game game;
	bool isSuccess = game.Initialize();

	if (isSuccess) {
		game.RunLoop();
	}

	game.ShutDown();

	return 0;
}
