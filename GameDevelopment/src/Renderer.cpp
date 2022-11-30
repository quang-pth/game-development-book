#include "include/Renderer.h"
#include "include/SpriteComponent.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/VertexArray.h"
#include "include/Mesh.h"
#include <SDL2/SDL_image.h>

Renderer::Renderer() :
	mSpriteShader(nullptr),
	mSpriteVertices(nullptr),
	mSprites(), mTextures(), mMeshes(),
	mGlewExperimental(GL_FALSE),
	mWindowWidth(0.0f), mWindowHeight(0.0f),
	mWindow(), mContext()
{

}

Renderer::~Renderer()
{
}

bool Renderer::Intialize(float screenWidth, float screenHeight)
{
	mWindowWidth = screenWidth;
	mWindowHeight = screenHeight;
	
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
	mGlewExperimental = GL_TRUE; // Prevent init error when using core context on some platforms
	if (glewInit() != GLEW_OK) {
		SDL_Log("Failed to initialize GLEW!");
		return false;
	}
	glGetError();

	IMG_Init(IMG_INIT_PNG);

	this->InitSpriteVertices();
	if (!this->LoadShaders()) {
		return false;
	}

	return true;
}

void Renderer::ShutDown()
{
	delete mSpriteVertices;

	mSpriteShader->Unload();
	delete mSpriteShader;
	
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);

	IMG_Quit();
	SDL_Quit();
}

void Renderer::Unload()
{
	for (std::pair<const std::string&, Texture*> iter : mTextures) {
		iter.second->Unload();
		delete iter.second;
	}
	mTextures.clear();
	for (std::pair<const std::string&, Mesh*> iter : mMeshes) {
		iter.second->Unload();
		delete iter.second;
	}
	mMeshes.clear();
}

void Renderer::Draw()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteShader->SetActive();
	mSpriteVertices->SetActive();

	for (SpriteComponent* sprite : mSprites) {
		sprite->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
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

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	// Get texture if already loaded
	std::unordered_map<std::string, Texture*>::iterator iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		return mTextures[fileName];
	}

	Texture* texture = new Texture();
	if (!texture->Load(fileName)) 
		return nullptr;

	mTextures.insert({ fileName, texture });
	return texture;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	std::unordered_map<std::string, Mesh*>::iterator iter = mMeshes.find(fileName);
	if (iter != mMeshes.end()) {
		return mMeshes[fileName];
	}

	Mesh* mesh = new Mesh();

	if (!mesh->Load(fileName, this)) {
		return nullptr;
	};
	mMeshes.insert({ fileName, mesh });

	return mesh;
}

bool Renderer::LoadShaders()
{
	mSpriteShader = new Shader();

	if (!mSpriteShader->Load("Shader/sprite-vert.glsl", "Shader/sprite-frag.glsl")) {
		return false;
	}

	mSpriteShader->SetActive();
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(
		static_cast<float>(mWindowWidth),
		static_cast<float>(mWindowHeight)
	);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	return true;
}

void Renderer::InitSpriteVertices()
{
	// Vertex buffer
	float vertexBuffer[] = {
		// Position		 //Color			// Texel - invert the V coordinate
	   -0.5f,  0.5f, 0.0f,	-0.5f,  0.5f, 0.0f,	 0.0f,  0.0f, // top-left
		0.5f,  0.5f, 0.0f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,	 // top-right
		0.5f, -0.5f, 0.0f,  0.5f, -0.5f, 0.0f,  1.0f,  1.0f,  // bottom-right
	   -0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f,  0.0f,  1.0f// bottom-left
	};
	std::uint32_t indexBuffer[] = {
		0, 1, 2, // First triangle
		2, 3, 0, // Second triangle
	};
	mSpriteVertices = new VertexArray(vertexBuffer, sizeof(vertexBuffer) / sizeof(float),
		indexBuffer, sizeof(indexBuffer) / sizeof(std::uint32_t));
}
