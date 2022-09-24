#include "include/Game.h"
#include <iostream>

const unsigned int numberOfBall = 2;

Game::Game() : mWindow(nullptr), mIsRunning(true), mTicksCount(0.0f), 
			mRenderer(), mPaddleHeight1(90), mPaddleHeight2(90)
{
	mWindowWidth = 800;
	mWindowHeight = 600;
	// Ball
	for (unsigned int i = 0; i < numberOfBall; i++) {
		Ball ball;
		ball.position.x = mWindowWidth / 2.0f;
		ball.position.y = mWindowHeight / 2.0f;
		if (i == 0) {
			ball.velocity.x = -200.0f;
			ball.velocity.y = 235.0f;
		}
		else {
			ball.velocity.x = 200.0f;
			ball.velocity.y = -235.0f;
		}
		mBalls.push_back(ball);
	}
	// Paddle 1
	mPaddlePos1.x = 7.5;
	mPaddlePos1.y = 600 / 2;
	// Paddle 2
	mPaddlePos2.x = 800;
	mPaddlePos2.y = 600 / 2;
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
	mWindow = SDL_CreateWindow("Game Window", 100, 40, mWindowWidth, mWindowHeight, 0);
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
	// Paddle 1 direction
	mPaddleDir1 = 0;
	if (keyboardState[SDL_SCANCODE_W]) {
		mPaddleDir1 -= 1;
	}
	if (keyboardState[SDL_SCANCODE_S]) {
		mPaddleDir1 += 1;
	}
	// Paddle 2 direction
	mPaddleDir2 = 0;
	if (keyboardState[SDL_SCANCODE_I]) {
		mPaddleDir2 -= 1;
	}
	if (keyboardState[SDL_SCANCODE_K]) {
		mPaddleDir2 += 1;
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

	// Move Paddle 1
	mPaddlePos1.y += mPaddleDir1 * 300.0f * deltaTime;
	if (mPaddlePos1.y - mPaddleHeight1 / 2.0f - 5.0f <= 0) {
		mPaddlePos1.y = mPaddleHeight1 / 2.0f + 5.0f;
	}
	else if (mPaddlePos1.y > mWindowHeight - mPaddleHeight1 / 2.0f - 5.0f) {
		mPaddlePos1.y = mWindowHeight - mPaddleHeight1 / 2.0f - 5.0f;
	}
	// Move Paddle 2
	mPaddlePos2.y += mPaddleDir2 * 300.0f * deltaTime;
	if (mPaddlePos2.y - mPaddleHeight2 / 2.0f - 5.0f <= 0) {
		mPaddlePos2.y = mPaddleHeight2 / 2.0f + 5.0f;
	}
	else if (mPaddlePos2.y > mWindowHeight - mPaddleHeight2 / 2.0f - 5.0f) {
		mPaddlePos2.y = mWindowHeight - mPaddleHeight2 / 2.0f - 5.0f;
	}

	for (Ball& ball : mBalls) {
		ball.position.x += ball.velocity.x * deltaTime;
		ball.position.y += ball.velocity.y * deltaTime;
		// Collide top wall
		if (ball.position.y < mThickness / 2.0f && ball.velocity.y < 0.0f) {
			ball.velocity.y *= -1;
		}
		// Collide bottom wall
		if (ball.position.y > mWindowHeight - mThickness / 2.0f && ball.velocity.y > 0.0f) {
			ball.velocity.y *= -1;
		}
		// Collide Left Paddle
		if (std::abs(ball.position.y - mPaddlePos1.y) < mPaddleHeight1 / 2.0f
			&& ball.position.x > 0.0f && ball.position.x < mPaddlePos1.x + mThickness / 2.0f
			&& ball.velocity.x < 0.0f
			) {
			ball.velocity.x *= -1;
		}
		// Collide Right Paddle
		if (std::abs(ball.position.y - mPaddlePos2.y) < mPaddleHeight2 / 2.0f
			&& ball.position.x < mWindowWidth && ball.position.x > mPaddlePos2.x - mThickness
			&& ball.velocity.x > 0.0f
			) {
			ball.velocity.x *= -1;
		}
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);
	// Draw objects on the scene
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	for (Ball& ball : mBalls) {
		SDL_Rect ballRect{
			static_cast<int>(ball.position.x - mThickness / 2),
			static_cast<int>(ball.position.y - mThickness / 2),
			mThickness,
			mThickness,
		};
		SDL_RenderFillRect(mRenderer, &ballRect);
	}
	SDL_Rect paddle1{
		static_cast<int>(mPaddlePos1.x - mThickness / 2),
		static_cast<int>(mPaddlePos1.y - mPaddleHeight1 / 2),
		mThickness,
		mPaddleHeight1,
	};
	SDL_RenderFillRect(mRenderer, &paddle1);
	SDL_Rect paddle2{
		static_cast<int>(mPaddlePos2.x - mThickness),
		static_cast<int>(mPaddlePos2.y - mPaddleHeight2 / 2),
		mThickness,
		mPaddleHeight2,
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

	// Swap back and front color buffer
	SDL_RenderPresent(mRenderer);
}
