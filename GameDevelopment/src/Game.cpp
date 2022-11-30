#include"include/Game.h"
#include"include/GameObject.h"
#include"include/CooldownManager.h"
#include"include/SpriteComponent.h"
#include"include/BackgroundSpriteComponent.h"
#include"include/TransformComponent.h"
#include"include/TileMapComponent.h"
#include"include/Ship.h"
#include"include/Asteroid.h"
#include"include/VertexArray.h"
#include"include/Texture.h"
#include<include/Shader.h>

#include<SDL2/SDL_image.h>
#include<iostream>

Game::Game() :
	mWindow(nullptr), mIsRunning(true),
	mTicksCount(0.0f), mContext(),
	mUpdatingGameObjects(false),
	mWindowWidth(800), mWindowHeight(600), mShip(nullptr),
	glewExperimental(GL_TRUE),
	mSpriteShader(), mSpriteVertices()
{
	mCooldownManager = new CooldownManager(this);
}

bool Game::Initialize()
{
	// Init SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	// Config OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Use OpenGL version 330
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Config RGBA channel with 32 pixel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double-buffering
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // Run OpenGL on GPU
	// Init Window
	mWindow = SDL_CreateWindow("Graphics with OpenGL 330", 100, 40, mWindowWidth, mWindowHeight, 
		SDL_WINDOW_OPENGL);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	// Create OpenGL Context
	mContext = SDL_GL_CreateContext(mWindow);
	// Init OpenGL extension functions
	glewExperimental = GL_TRUE; // Prevent init error when using core context on some platforms
	if (glewInit() != GLEW_OK) {
		SDL_Log("Failed to initialize GLEW!");
		return false;
	}
	glGetError();

	// Init Load Sprite format
	IMG_Init(IMG_INIT_PNG);

	if (!this->LoadShaders()) 
		return false;

	this->InitSpriteVertices();

	this->LoadData();

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
	IMG_Quit();
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

bool Game::LoadShaders()
{
	mSpriteShader = new Shader();

	if (!mSpriteShader->Load("Shader/sprite-vert.glsl", "Shader/sprite-frag.glsl")) {
		return false;
	}

	mSpriteShader->SetActive();
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(static_cast<float>(mWindowWidth), 
		static_cast<float>(mWindowHeight));
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	
	return true;
}

void Game::InitSpriteVertices()
{
	// Vertex buffer
	float vertexBuffer[] = {
		 // Position		// Texel - invert the V coordinate
		-0.5f,  0.5f, 0.0f,	 0.0f,  0.0f, // top-left
		 0.5f,  0.5f, 0.0f,	 1.0f,  0.0f,	 // top-right
		 0.5f, -0.5f, 0.0f,  1.0f,  1.0f,  // bottom-right
		-0.5f, -0.5f, 0.0f,  0.0f,  1.0f// bottom-left
	};
	std::uint32_t indexBuffer[] = {
		0, 1, 2, // First triangle
		2, 3, 0, // Second triangle
	};
	mSpriteVertices = new VertexArray(vertexBuffer, sizeof(vertexBuffer) / sizeof(float),
		indexBuffer, sizeof(indexBuffer) / sizeof(std::uint32_t));
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

float dt;
void Game::UpdateGame()
{
	// Limit game runs on 60FPS
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	// Game delta time measured in seconds
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();
	dt = deltaTime;

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
	std::vector<GameObject*> deadActors;
	for (GameObject* gameObject : mGameObjects) {
		if (gameObject->GetState() == GameObject::State::EDead) {
			deadActors.emplace_back(gameObject);
		}
	}
	// Delete dead gameobjects
	for (GameObject* gameObject : deadActors) {
		delete gameObject;
	}
}

static float transitionDuration = 2.0f;
static Vector3 colors[] = {
	Vector3(1.0f, 0.0f, 0.0f),
	Vector3(0.0f, 1.0f, 0.0f),
	Vector3(0.0f, 0.0f, 1.0f),
};

static uint8_t colorIdx = 0;
static float transFactor = 0.4f;
static Vector3 currentColor = colors[colorIdx];
static Vector3 nextColor = colors[colorIdx + 1];

void Game::GenerateOutput()
{
	transitionDuration -= dt * transFactor;
	if (transitionDuration < 0.0f) {
		transitionDuration = 2.0f;

		colorIdx = (++colorIdx + 1) % 3;
		nextColor = colors[colorIdx];
	}

	currentColor = Vector3::Lerp(currentColor, nextColor, dt * transFactor);

	glClearColor(currentColor.x, currentColor.y, currentColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteShader->SetActive();
	mSpriteVertices->SetActive();

	for (auto sprite : mSprites) {
		sprite->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}

void Game::LoadData()
{
	mShip = new Ship(this);

	for (unsigned int i = 0; i < 20; i++) {
		mAsteroids.emplace_back(new Asteroid(this));
	}

	//GameObject* background = new GameObject(this, "Background");
	//background->GetTransform()->SetPosition(Vector2(mWindowWidth / 2.0f, mWindowHeight / 2.0f));
	//// Far background
	//BackgroundSpriteComponent* farBackgroundComponent = new BackgroundSpriteComponent(background, 10);
	//farBackgroundComponent->SetScreenSize(Vector2(mWindowWidth, mWindowHeight));
	//std::vector<SDL_Texture*> farBackgroundTextures = {
	//	GetTexture("Assets/Chapter2/Farback01.png"),
	//	GetTexture("Assets/Chapter2/Farback02.png"),
	//};
	//farBackgroundComponent->SetBackgroundTextures(farBackgroundTextures);
	//farBackgroundComponent->SetScrollSpeed(-100.0f);
	//// Near background
	//BackgroundSpriteComponent* nearBackgroundComponent = new BackgroundSpriteComponent(background, 50);
	//nearBackgroundComponent->SetScreenSize(Vector2(mWindowWidth, mWindowHeight));
	//std::vector<SDL_Texture*> nearBackgroundTextures = {
	//	GetTexture("Assets/Chapter2/Stars.png"),
	//	GetTexture("Assets/Chapter2/Stars.png"),
	//};
	//nearBackgroundComponent->SetBackgroundTextures(nearBackgroundTextures);
	//nearBackgroundComponent->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
	while (!mGameObjects.empty()) {
		delete mGameObjects.back();
	}
	mGameObjects.clear();
	for (std::pair<const std::string&, Texture*> iter : mTextures) {
		iter.second->Unload();
	}
	mTextures.clear();
	mSpriteShader->Unload();
}

Texture* Game::GetTexture(const std::string& fileName)
{
	// Get texture if already loaded
	std::unordered_map<std::string, Texture*>::iterator iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		return mTextures[fileName];
	}

	Texture* texture = new Texture();
	if (!texture->Load(fileName)) return nullptr;

	return texture;
}

std::vector<class Asteroid*> Game::GetAsteroids() const
{
	return mAsteroids;
}

Ship* Game::GetShip() const
{
	return mShip;
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
