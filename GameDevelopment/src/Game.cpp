#include "include/Game.h"
#include <iostream>

Game::Game() : mWindow(nullptr), mIsRunning(true), mTicksCount(0.0f), mRenderer(), mPaddleHeight(90)
{
	// Ball
	mBallPos.x = 800 / 2;
	mBallPos.y = 600 / 2;
	mBallVelocity.x = -200.0f;
	mBallVelocity.y = 235.0f;

	// Paddle
	mPaddlePos.x = 7.5;
	mPaddlePos.y = 600 / 2;
}

bool Game::Initialize()
{
	// Init SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	// Init Window
	mWindow = SDL_CreateWindow("Game Window", 100, 40, 800, 600, 0);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	// Init Renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ShutDown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// Process keyboard event
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	// Paddle direction
	mPaddleDir = 0;
	if (keyboardState[SDL_SCANCODE_W]) {
		mPaddleDir -= 1;
	}
	if (keyboardState[SDL_SCANCODE_S]) {
		mPaddleDir += 1;
	}
}

void Game::UpdateGame()
{
	// Force game run on 60FPS
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	// Game delta time measured in seconds
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();

	// Clamp the delta time for debugging
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	// Paddle
	mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
	if (mPaddlePos.y - mPaddleHeight / 2.0f - 5.0f <= 0) {
		mPaddlePos.y = mPaddleHeight / 2.0f + 5.0f;
	}
	else if (mPaddlePos.y > 600 - mPaddleHeight / 2.0f - 5.0f) {
		mPaddlePos.y = 600 - mPaddleHeight / 2.0f - 5.0f;
	}

	// Ball
	mBallPos.x += mBallVelocity.x * deltaTime;
	mBallPos.y += mBallVelocity.y * deltaTime;
	// Top wall
	if (mBallPos.y < 7.5f && mBallVelocity.y < 0.0f) {
		mBallVelocity.y *= -1;
	}	
	// Bottom wall
	if (mBallPos.y > 600.0f - 7.5f && mBallVelocity.y > 0.0f) {
		mBallVelocity.y *= -1;
	}
	// Right wall
	if (mBallPos.x > 800.0f - 7.5f && mBallVelocity.x > 0.0f) {
		mBallVelocity.x *= -1;
	}
	
	if (std::abs(mBallPos.y - mPaddlePos.y) <= mPaddleHeight / 2.0f
		&& mBallPos.x > 0.0f && mBallPos.x <= mPaddlePos.x + 7.5f
		&& mBallVelocity.x < 0.0f
	) {
		mBallVelocity.x *= -1;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);
	// Draw objects on the scene
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	const int thickness = 15;
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness,
	};
	SDL_RenderFillRect(mRenderer, &ball);
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x - thickness / 2),
		static_cast<int>(mPaddlePos.y - mPaddleHeight / 2),
		thickness,
		mPaddleHeight,
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// Swap back and front color buffer
	SDL_RenderPresent(mRenderer);
}
