#include"include/Game.h"
#include"include/GameObject.h"

#include"include/CooldownManager.h"
#include"include/SpriteComponent.h"
#include"include/BackgroundSpriteComponent.h"
#include"include/TransformComponent.h"
#include"include/MeshComponent.h"
#include"include/TileMapComponent.h"

#include"include/Level.h"
#include"include/Camera.h"
#include"include/Sphere.h"
#include"include/Cube.h"
#include"include/Icon.h"
#include"include/VertexArray.h"
#include"include/Texture.h"
#include"include/Mesh.h"
#include"include/Shader.h"
#include"include/Renderer.h"

#include<iostream>

Game::Game() :
	mIsRunning(true),
	mTicksCount(0.0f),
	mUpdatingGameObjects(false),
	mWindowWidth(800), mWindowHeight(600), 
	mShip(nullptr), mRenderer(nullptr)
{
	mCooldownManager = new CooldownManager(this);
}

bool Game::Initialize()
{
	mRenderer = new Renderer(this);
	
	if (!mRenderer->Intialize(mWindowWidth, mWindowHeight)) {
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	};
	
	this->LoadData();

	if (!mRenderer->BeginScene(mCamera)) {
		return false;
	}

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning) {		
		this->ProcessInput();
		this->UpdateGame();
		this->GenerateOutput();
	}
}

void Game::ShutDown()
{
	this->UnloadData();
	
	if (mRenderer)
		mRenderer->ShutDown();
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

	mUpdatingGameObjects = true;
	for (GameObject* gameObject : mGameObjects) {
		gameObject->ProcessInput(keyboardState);
	}
	mUpdatingGameObjects = false;
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
		gameObject->GetTransform()->ComputeWorldTransform();
		mGameObjects.emplace_back(gameObject);
	}
	mPendingGameObjects.clear();
	// Get dead gameobjects
	std::vector<GameObject*> deadGameObjects;
	for (GameObject* gameObject : mGameObjects) {
		if (gameObject->GetState() == GameObject::State::EDead) {
			deadGameObjects.emplace_back(gameObject);
		}
	}
	// Delete dead gameobjects
	for (GameObject* gameObject : deadGameObjects) {
		delete gameObject;
	}
	deadGameObjects.clear();
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::LoadData()
{
	mCamera = new Camera(this);

	new Level(this);
	new Sphere(this);
	new Cube(this);
	
	Icon* healthbar = new Icon(this);
	healthbar->SetTexture(mRenderer->GetTexture("Assets/Chapter6/HealthBar.png"));
	healthbar->GetTransform()->SetScale(8.0f, 1.0f, 1.0f);
	healthbar->GetTransform()->SetPosition(Vector3(-mWindowWidth / 2.0f + 150.0f, -mWindowHeight / 2.0f + 100.0f, 0.0f));
	
	Icon* radar = new Icon(this);
	radar->SetTexture(mRenderer->GetTexture("Assets/Chapter6/Radar.png"));
	radar->GetTransform()->SetScale(5.0f);
	radar->GetTransform()->SetPosition(Vector3(mWindowWidth / 2.0f - 100.0f, -mWindowHeight / 2.0f + 100.0f, 0.0f));
}

void Game::UnloadData()
{
	while (!mGameObjects.empty()) {
		delete mGameObjects.back();
	}
	mGameObjects.clear();
	
	if (mRenderer) 
		mRenderer->Unload();
}

Camera* Game::GetCamera() const
{
	return mCamera;
}

Renderer* Game::GetRenderer() const
{
	return mRenderer;
}

int Game::GetWindowWidth() const
{
	return mWindowWidth;
}

int Game::GetWindowHeight() const
{
	return mWindowHeight;
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