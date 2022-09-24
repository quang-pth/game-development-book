#pragma once

#include<SDL2/SDL.h>

struct Vector2 {
	float x;
	float y;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	float mTicksCount; // Measured in miliseconds

	// Game Objects
	Vector2 mBallPos;
	Vector2 mBallVelocity;

	Vector2 mPaddlePos;
	int mPaddleDir;
	int mPaddleHeight;
};

