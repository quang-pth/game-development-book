#include"include/Game.h"
#include"include/GameObject.h"
#include"include/CooldownManager.h"
#include"include/SpriteComponent.h"
#include"include/BackgroundSpriteComponent.h"
#include"include/TransformComponent.h"
#include"include/TileMap.h"
#include"include/StateManager.h"
#include"include/Mario.h"
#include"include/OrchidOwl.h"
#include"include/AIComponent.h"
#include"include/Asteroid.h"
#include"include/AIPatrol.h"
#include"include/AIAttack.h"
#include"include/AIDeath.h"
#include"include/Unit.h"
#include<SDL2/SDL_image.h>
#include<box2D/b2_math.h>
#include<iostream>

Game::Game() : 
	mpWindow(nullptr), mIsRunning(true), 
	mTicksCount(0.0f), mpRenderer(), mpUpdatingGameObjects(false), 
	mWindowWidth(800), mWindowHeight(640),
	mHero(nullptr), mTilemap(nullptr), 
	mCooldownManager(nullptr), mStateManager(nullptr),
	mVelocityIterations(7), mPositionIterations(3),
	mPhysicWorld(b2Vec2(0.0f, 10.0f)),
	mEnemies()
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
	mpWindow = SDL_CreateWindow("Rocket To The Moon", 100, 40, mWindowWidth, mWindowHeight, 0);
	if (!mpWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	// Init Renderer
	mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mpRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	// Init Load Sprite format
	IMG_Init(IMG_INIT_PNG);

	this->LoadData();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		mPhysicWorld.Step(1 / 60.0f, mVelocityIterations, mPositionIterations);
		GenerateOutput();
	}
}

void Game::ShutDown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mpRenderer);
	SDL_DestroyWindow(mpWindow);
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

	mpUpdatingGameObjects = true;
	for (const auto& gameObject : mpGameObjects) {
		gameObject->ProcessInput(keyboardState);
	}
	mpUpdatingGameObjects = false;
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
	mpUpdatingGameObjects = true;
	for (const auto& gameObject : mpGameObjects) {
		gameObject->Update(deltaTime);
	}
	mpUpdatingGameObjects = false;
	// Add pending gameobject
	for (const auto& gameObject : mpPendingGameObjects) {
		mpGameObjects.emplace_back(gameObject);
	}
	mpPendingGameObjects.clear();
	// Get dead gameobjects
	std::vector<GameObject*> deadGameObjects;
	for (const auto& gameObject : mpGameObjects) {
		if (gameObject->GetState() == GameObject::State::EDead) {
			deadGameObjects.emplace_back(gameObject);
		}
	}
	// Delete dead gameobjects
	for (const auto& gameObject : deadGameObjects) {
		delete gameObject;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mpRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mpRenderer);
	// Draw objects on the scene
	for (const auto& sprite : mpSprites) {
		sprite->Draw(mpRenderer);
	}
	// Swap back and front color buffer
	SDL_RenderPresent(mpRenderer);
}

void Game::LoadData()
{
	mCooldownManager = new CooldownManager(this);

	mHero = new Hero(this);
	OrchidOwl* owl = new OrchidOwl(this);
	mEnemies.emplace_back(owl);

	GameObject* background = new GameObject(this, "Background");
	background->pTransform->SetPosition(Vector2(mWindowWidth / 2.0f, mWindowHeight / 2.0f));
	// Far background
	BackgroundSpriteComponent* farBackgroundComponent = 
		new BackgroundSpriteComponent(background, 10, "BackgroundSprite1");
	farBackgroundComponent->SetScreenSize(Vector2(mWindowWidth, mWindowHeight));
	std::vector<SDL_Texture*> farBackgroundTextures = {
		GetTexture("Assets/Chapter2/Farback01.png"),
		GetTexture("Assets/Chapter2/Farback02.png"),
	};
	farBackgroundComponent->SetBackgroundTextures(farBackgroundTextures);
	farBackgroundComponent->SetScrollSpeed(-100.0f);
	// Near background
	BackgroundSpriteComponent* nearBackgroundComponent = 
		new BackgroundSpriteComponent(background, 50, "BackgroundSprite2");
	nearBackgroundComponent->SetScreenSize(Vector2(mWindowWidth, mWindowHeight));
	std::vector<SDL_Texture*> nearBackgroundTextures = {
		GetTexture("Assets/Chapter2/Stars.png"),
		GetTexture("Assets/Chapter2/Stars.png"),
	};
	nearBackgroundComponent->SetBackgroundTextures(nearBackgroundTextures);
	nearBackgroundComponent->SetScrollSpeed(-200.0f);

	mTilemap = new TileMap(this);
	mTilemap->SetTileDimension(Vector2(TILE_SIZE, TILE_SIZE));
	mTilemap->SetScale(2.0f);
	mTilemap->SetTilePerRow(TILE_PER_ROW);
	mTilemap->Init("Assets/Shooter/spritesheet.png", "Assets/Shooter/level-one-half-dimension.csv");
}

void Game::UnloadData()
{
	while (!mpGameObjects.empty()) {
		delete mpGameObjects.back();
	}

	for (std::pair<const std::string&, SDL_Texture*> i : mpTextures) {
		SDL_DestroyTexture(i.second);
	}

	mpTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	// Get texture if already loaded
	std::unordered_map<std::string, SDL_Texture*>::iterator iter = mpTextures.find(fileName);
	if (iter != mpTextures.end()) {
		return mpTextures[fileName];
	}
	// Else load new texture
	SDL_Surface* surf = IMG_Load(fileName.c_str());
	if (!surf) {
		SDL_Log("Failed to load image file %s: ", SDL_GetError());
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(mpRenderer, surf);
	SDL_FreeSurface(surf);
	if (!texture) {
		SDL_Log("Failed to convert from surface to texture %s: ", SDL_GetError());
		return nullptr;
	}

	mpTextures.emplace(fileName.c_str(), texture);
	return texture;
}

Hero* Game::GetHero() const
{
	return mHero;
}

std::vector<class Enemy*> Game::GetEnemies() const
{
	return mEnemies;
}

TileMap* Game::GetTileMap() const
{
	return mTilemap;
}

CooldownManager* Game::GetCooldownManager() const
{
	return mCooldownManager;
}

int Game::GetWindowWidth() const
{
	return mWindowWidth;
}

int Game::GetWindowHeight() const
{
	return mWindowHeight;
}

Vector2 Game::GetCenterPoint() const
{
	return Vector2(mWindowWidth / 2, mWindowHeight / 2);
}

b2World* Game::GetPhysicWorld()
{
	return &mPhysicWorld;
}

void Game::AddGameObject(GameObject* gameObject)
{
	if (mpUpdatingGameObjects) {
		mpPendingGameObjects.emplace_back(gameObject);
	}
	else {
		mpGameObjects.emplace_back(gameObject);
	}
}

void Game::RemoveGameObject(GameObject* gameObject)
{
	auto iter = std::find(mpPendingGameObjects.begin(), mpPendingGameObjects.end(), gameObject);
	if (iter != mpPendingGameObjects.end()) {
		mpPendingGameObjects.erase(iter);
	}
	iter = std::find(mpGameObjects.begin(), mpGameObjects.end(), gameObject);
	if (iter != mpGameObjects.end()) {
		mpGameObjects.erase(iter);
	}	
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int currentSpriteDrawOrder = sprite->GetDrawOrder();
	auto iter = mpSprites.begin();
	for (; iter != mpSprites.end(); iter++) {
		if (currentSpriteDrawOrder < (*iter)->GetDrawOrder()) {
			break;
		}
	}
	mpSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mpSprites.begin(), mpSprites.end(), sprite);
	if (iter != mpSprites.end()) {
		mpSprites.erase(iter);
	}
}
