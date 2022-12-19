#include"include/Game.h"
#include"include/GameObject.h"
#include"include/SpriteComponent.h"
#include"include/BackgroundSpriteComponent.h"
#include"include/TransformComponent.h"
#include"include/MeshComponent.h"
#include"include/TileMapComponent.h"
#include"include/Level.h"
#include"include/AudioSystem.h"
#include"include/Camera.h"
#include"include/Sphere.h"
#include"include/Cube.h"
#include"include/Icon.h"
#include"include/VertexArray.h"
#include"include/Texture.h"
#include"include/Mesh.h"
#include"include/Shader.h"
#include"include/Renderer.h"
#include"include/InputSystem.h"
#include<iostream>

Game::Game() :
	mIsRunning(true),
	mTicksCount(0.0f),
	mUpdatingGameObjects(false),
	mWindowWidth(800), mWindowHeight(600), 
	mRenderer(nullptr), mCamera(nullptr), mAudioSystem(nullptr), mInputSystem(nullptr),
	mMusicEvent(), mReverbSnap()
{
}

bool Game::Initialize()
{
	mAudioSystem = new AudioSystem(this);
	if (!mAudioSystem->Initialize()) {
		return false;
	}

	mRenderer = new Renderer(this);
	if (!mRenderer->Intialize(mWindowWidth, mWindowHeight)) {
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	};
	
	mInputSystem = new InputSystem(this);
	mInputSystem->Initialize();
	mInputSystem->SetRelativeMouseMode(false);

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
	mRenderer->ShutDown();
	mAudioSystem->Shutdown();
	mInputSystem->Shutdown();
}

void Game::ProcessInput()
{
	mInputSystem->PrepareBeforeUpdate();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_KEYDOWN:
			if (!e.key.repeat) {
				this->HandlKeyPress(e.key.keysym.sym);
			}
			break;
		default:
			mInputSystem->ProcessEvent(e);
			break;
		}
	}

	mInputSystem->Update();
	const InputState& state = mInputSystem->GetInputState();
	if (state.KeyBoard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::EReleased) {
 		mIsRunning = false;
	}
	
	mUpdatingGameObjects = true;
	for (GameObject* gameObject : mGameObjects) {
		gameObject->ProcessInput(state);
	}
	mUpdatingGameObjects = false;
}

void Game::HandlKeyPress(std::uint32_t key)
{
	float volume, value;
	switch (key) {
	case '-':
		// Reduce master volume
		volume = mAudioSystem->GetBusVolume("bus:/");
		volume = Math::Max(0.0f, volume - 0.1f);
		mAudioSystem->SetBusVolume("bus:/", volume);
		break;
	case '=':
		// Increase master volume
		volume = mAudioSystem->GetBusVolume("bus:/");
		volume = Math::Min(1.0f, volume + 0.1f);
		mAudioSystem->SetBusVolume("bus:/", volume);
		break;
	case 'e':
		// Play explosion
		mAudioSystem->PlayEvent("event:/Explosion2D");
		break;
	case 'm':
		// Toggle background music pause state
		mMusicEvent.SetPaused(!mMusicEvent.GetPaused());
		break;
	case 'r':
		// Enable/Disable reverb on SFX bus
		if (!mReverbSnap.IsValid()) {
			mReverbSnap = mAudioSystem->PlayEvent("snapshot:/WithReverb");
		}
		else {
			mReverbSnap.Stop();
		}
		break;
	case '1':
		// Set footstep parameter to default
		value = 0.0f;
		mCamera->SetFootstepSurface(value);
		break;
	case '2':
		// Set footstep parameter to grass
		value = 0.5f;
		mCamera->SetFootstepSurface(value);
		break;
	default:
		break;
	}
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
	// ============ AUDIO SYSTEM ==================
	mAudioSystem->Update(deltaTime);
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
	
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");
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

AudioSystem* Game::GetAudioSystem() const
{
	return mAudioSystem;
}

InputSystem* Game::GetInputSystem() const
{
	return mInputSystem;
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