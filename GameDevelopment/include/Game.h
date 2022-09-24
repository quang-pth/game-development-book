#pragma once

#include<SDL2/SDL.h>
#include<vector>

struct Vector2 {
	float x;
	float y;
};

struct Ball {
	Vector2 position;
	Vector2 velocity;
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
	int mWindowWidth;
	int mWindowHeight;

	// Balls
	std::vector<Ball> mBalls;
	// Player 1 
	Vector2 mPaddlePos1;
	int mPaddleDir1;
	int mPaddleHeight1;
	// Player 2 
	Vector2 mPaddlePos2;
	int mPaddleDir2;
	int mPaddleHeight2;

	const float mThickness = 15.0f;
};

