#include<include/Game.h>
#include<include/EulerAngle.h>
#include <iostream>

int main(int argc, char* args[]) {
	Game game;
	bool isSuccess = game.Initialize();
	if (isSuccess) {
		game.RunLoop();
	}
	game.ShutDown();

	return 0;
}
