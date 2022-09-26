#include "include/Game.h"
#include"include/Actor.h"
#include"include/SpriteComponent.h"
#include"include/BackgroundSpriteComponent.h"
#include"include/Ship.h"
#include<SDL2/SDL_image.h>
#include <iostream>

Game::Game() : mWindow(nullptr), mIsRunning(true), mTicksCount(0.0f), 
			mRenderer(), mUpdatingActors(false), mWindowWidth(800), mWindowHeight(600), mShip(nullptr)
{
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
	mWindow = SDL_CreateWindow("Rocket To The Moon", 100, 40, mWindowWidth, mWindowHeight, 0);
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
	// Init Load Sprite format
	IMG_Init(IMG_INIT_PNG);

	LoadData();

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
	UnloadData();
	IMG_Quit();
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
	mShip->ProcesKeyboard(keyboardState);
}

void Game::UpdateGame()
{
	// Limit game runs on 60FPS
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	// Game delta time measured in seconds
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();

	// Clamp the delta time for debugging
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	// Update game objects
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;
	// Add pending actors 
	for (auto actor : mPendingActors) {
		mActors.emplace_back(actor);
	}
	mPendingActors.clear();
	// Get dead actors
	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}
	// Delete dead actors
	for (auto actor : deadActors) {
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);
	// Draw objects on the scene
	for (auto sprite : mSprites) {
		sprite->Draw(mRenderer);
	}
	// Swap back and front color buffer
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);
	// Background actors
	Actor* backgroundActor = new Actor(this);
	backgroundActor->SetPosition(Vector2(mWindowWidth / 2.0f, mWindowHeight / 2.0f));
	// Far background
	BackgroundSpriteComponent* farBackground = new BackgroundSpriteComponent(backgroundActor);
	farBackground->SetScreenSize(Vector2(mWindowWidth, mWindowHeight));
	std::vector<SDL_Texture*> farBackgroundTextures = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png"),
	};
	farBackground->SetBackgroundTextures(farBackgroundTextures);
	farBackground->SetScrollSpeed(-100.0f);
	// Near background
	BackgroundSpriteComponent* nearBackground = new BackgroundSpriteComponent(backgroundActor, 50);
	nearBackground->SetScreenSize(Vector2(mWindowWidth, mWindowHeight));
	std::vector<SDL_Texture*> nearBackgroundTextures = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png"),
	};
	nearBackground->SetBackgroundTextures(nearBackgroundTextures);
	nearBackground->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
	while (!mActors.empty()) {
		delete mActors.back();
	}
	for (auto i : mTextures) {
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	// Get texture if already loaded
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		return mTextures[fileName];
	}
	// Else load new texture
	SDL_Surface* surf = IMG_Load(fileName.c_str());
	if (!surf) {
		SDL_Log("Failed to load image file %s: ", SDL_GetError());
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	if (!texture) {
		SDL_Log("Failed to convert from surface to texture %s: ", SDL_GetError());
		return nullptr;
	}

	mTextures.emplace(fileName.c_str(), texture);
	return texture;
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		mPendingActors.erase(iter);
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		mActors.erase(iter);
	}	
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int currentSpriteDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); iter++) {
		if (currentSpriteDrawOrder < (*iter)->GetDrawOrder()) {
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}
