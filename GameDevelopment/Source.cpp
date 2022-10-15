#include <iostream>
#include <include/Game.h>

int main(int argc, char* args[]) 
{
	Game game;
	bool isInit = game.Initialize();
	if (isInit) {
		game.RunLoop();
	}

	game.ShutDown();

	return 0;
}
