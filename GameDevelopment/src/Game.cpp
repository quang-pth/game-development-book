#include"include/Game.h"
#include"include/GameObject.h"
#include"include/SpriteComponent.h"
#include"include/BackgroundSpriteComponent.h"
#include"include/TileMapComponent.h"
#include"include/Ship.h"
#include<SDL2/SDL_image.h>
#include<iostream>

Game::Game() : mWindow(nullptr), mIsRunning(true), mTicksCount(0.0f), 
			mRenderer(), mUpdatingGameObjects(false), mWindowWidth(800), mWindowHeight(600), mShip(nullptr)
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
	mUpdatingGameObjects = true;
	for (GameObject* gameObject : mGameObjects) {
		gameObject->Update(deltaTime);
	}
	mUpdatingGameObjects = false;
	// Add pending gameobject
	for (GameObject* gameObject : mPendingGameObjects) {
		mGameObjects.emplace_back(gameObject);
	}
	mPendingGameObjects.clear();
	// Get dead gameobjects
	std::vector<GameObject*> deadActors;
	for (GameObject* gameObject: mGameObjects) {
		if (gameObject->GetState() == GameObject::State::EDead) {
			deadActors.emplace_back(gameObject);
		}
	}
	// Delete dead gameobjects
	for (GameObject* gameObject : deadActors) {
		delete gameObject;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
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
	mShip->GetTransform()->SetPosition(Vector2(100.0f, 384.0f));
	mShip->GetTransform()->SetScale(1.5f);
	
	GameObject* background = new GameObject(this);
	background->GetTransform()->SetPosition(Vector2(mWindowWidth / 2.0f, mWindowHeight / 2.0f));
	// Far background
	BackgroundSpriteComponent* farBackgroundComponent = new BackgroundSpriteComponent(background);
	farBackgroundComponent->SetScreenSize(Vector2(mWindowWidth, mWindowHeight));
	std::vector<SDL_Texture*> farBackgroundTextures = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png"),
	};
	farBackgroundComponent->SetBackgroundTextures(farBackgroundTextures);
	farBackgroundComponent->SetScrollSpeed(-100.0f);
	// Near background
	BackgroundSpriteComponent* nearBackgroundComponent = new BackgroundSpriteComponent(background, 50);
	nearBackgroundComponent->SetScreenSize(Vector2(mWindowWidth, mWindowHeight));
	std::vector<SDL_Texture*> nearBackgroundTextures = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png"),
	};
	nearBackgroundComponent->SetBackgroundTextures(nearBackgroundTextures);
	nearBackgroundComponent->SetScrollSpeed(-200.0f);

	GameObject* tilemap = new GameObject(this);
	tilemap->GetTransform()->SetPosition(Vector2(0.0f, 0.0f));
	tilemap->GetTransform()->SetScale(0.79f);
	TileMapComponent* tileMapLayer1 = new TileMapComponent(tilemap);
	tileMapLayer1->Init("Assets/MapLayer1.csv");
}

void Game::UnloadData()
{
	while (!mGameObjects.empty()) {
		delete mGameObjects.back();
	}
	for (std::pair<const std::string&, SDL_Texture*> i : mTextures) {
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	// Get texture if already loaded
	std::unordered_map<std::string, SDL_Texture*>::iterator iter = mTextures.find(fileName);
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

void Game::AddGameObject(GameObject* gameObject)
{
	if (mUpdatingGameObjects) {
		mPendingGameObjects.emplace_back(gameObject);
	}
	else {
		mGameObjects.emplace_back(gameObject);
	}
}

void Game::RemoveGameObject(GameObject* gameObject)
{
	std::vector<GameObject*>::iterator iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), gameObject);
	if (iter != mPendingGameObjects.end()) {
		mPendingGameObjects.erase(iter);
	}

	iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
	if (iter != mGameObjects.end()) {
		mGameObjects.erase(iter);
	}	
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int currentSpriteDrawOrder = sprite->GetDrawOrder();
	std::vector<SpriteComponent*>::iterator iter = mSprites.begin();
	for (; iter != mSprites.end(); iter++) {
		if (currentSpriteDrawOrder < (*iter)->GetDrawOrder()) {
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	std::vector<SpriteComponent*>::iterator iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}
