#include "include/Renderer.h"
#include "include/Game.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"
#include "include/SpriteComponent.h"
#include "include/MeshComponent.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/VertexArray.h"
#include "include/Mesh.h"
#include <SDL2/SDL_image.h>

Renderer::Renderer(Game* game) :
	mGame(game),
	mSpriteShader(nullptr),
	mSpriteVertices(nullptr),
	mSprites(), mLoadedTextures(), mLoadedMeshes(),
	mGlewExperimental(GL_FALSE),
	mWindowWidth(0.0f), mWindowHeight(0.0f),
	mWindow(), mContext(), mCamera(nullptr), mMeshShader(nullptr),
	mAmbientLight(Vector3(0.2, 0.2, 0.2))
{
	mDirectionalLight.mDirection = Vector3(0, -.7f, -.7f);
	mDirectionalLight.mDiffuseColor = Vector3(0.0f, 1.0f, 0.0f);
	mDirectionalLight.mSpecularColor = Vector3(0.5f, 1.0f, 0.5f);
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
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Set OpenGL depth buffer context
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
	
	mMeshShader->Unload();
	delete mMeshShader;

	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);

	IMG_Quit();
	SDL_Quit();
}

void Renderer::Unload()
{
	for (std::pair<const std::string&, Texture*> iter : mLoadedTextures) {
		iter.second->Unload();
		delete iter.second;
	}
	mLoadedTextures.clear();
	for (std::pair<const std::string&, Mesh*> iter : mLoadedMeshes) {
		iter.second->Unload();
		delete iter.second;
	}
	mLoadedMeshes.clear();
}

void Renderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ============= MESH SHADER  =================
	glEnable(GL_DEPTH_TEST);
	mMeshShader->SetActive();
	mMeshShader->SetMatrixUniform("uViewMatrix", mViewMatrix);
	mMeshShader->SetMatrixUniform("uProjectionMatrix", mProjectionMatrix);
	for (MeshComponent* mesh : mMeshes) {
		mesh->Draw(mMeshShader);
	}
	glDisable(GL_DEPTH_TEST);
	// ============= END MESH SHADER  =================

	// ============= SPRITE SHADER  =================
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteShader->SetActive();
	mSpriteVertices->SetActive();

	for (SpriteComponent* sprite : mSprites) {
		sprite->Draw(mSpriteShader);
	}
	glDisable(GL_BLEND);
	// ============= END SPRITE SHADER  =================

	SDL_GL_SwapWindow(mWindow);
}

void Renderer::SetLightUniforms(Shader* shader)
{
	Matrix4 cameraView = mViewMatrix;
	cameraView.Invert();

	shader->SetActive();
	shader->SetVec3Uniform("uCameraPos", cameraView.GetTranslation());
	shader->SetVec3Uniform("uAmbientLight", mAmbientLight);
	shader->SetVec3Uniform("uDirLight.mDirection", mDirectionalLight.mDirection);
	shader->SetVec3Uniform("uDirLight.mDiffuseColor", mDirectionalLight.mDiffuseColor);
	shader->SetVec3Uniform("uDirLight.mSpecularColor", mDirectionalLight.mSpecularColor);
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

void Renderer::AddMesh(MeshComponent* mesh)
{
	auto iter = std::find(mMeshes.begin(), mMeshes.end(), mesh);
	if (iter == mMeshes.end()) {
		mMeshes.emplace_back(mesh);
	}
}

void Renderer::RemoveMesh(MeshComponent* mesh)
{
	auto iter = std::find(mMeshes.begin(), mMeshes.end(), mesh);
	if (iter != mMeshes.end()) {
		mMeshes.erase(iter);
	}
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	// Get texture if already loaded
	std::unordered_map<std::string, Texture*>::iterator iter = mLoadedTextures.find(fileName);
	if (iter != mLoadedTextures.end()) {
		return iter->second;
	}

	Texture* texture = new Texture();
	if (!texture->Load(fileName)) 
		return nullptr;

	mLoadedTextures.insert({ fileName, texture });
	return texture;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	std::unordered_map<std::string, Mesh*>::iterator iter = mLoadedMeshes.find(fileName);
	if (iter != mLoadedMeshes.end()) {
		return iter->second;
	}

	Mesh* mesh = new Mesh();

	if (!mesh->Load(fileName, this)) {
		return nullptr;
	};
	mLoadedMeshes.insert({ fileName, mesh });

	return mesh;
}

bool Renderer::LoadShaders()
{
	// =========== SPRITE SHADER ================
	mSpriteShader = new Shader();

	if (!mSpriteShader->Load("Shader/sprite-vert.glsl", "Shader/sprite-frag.glsl")) {
		delete mSpriteShader;
		mSpriteShader = nullptr;
		return false;
	}

	mSpriteShader->SetActive();
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(
		static_cast<float>(mWindowWidth),
		static_cast<float>(mWindowHeight)
	);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	// =========== END SPRITE SHADER ================

	// =========== MESH SHADER ================
	mMeshShader = new Shader();

	if (!mMeshShader->Load("Shader/phong-vert.glsl", "Shader/phong-frag.glsl")) {
		delete mMeshShader;
		mMeshShader = nullptr;
		return false;
	}

	mMeshShader->SetActive();
	// Construct view matrix
	mViewMatrix = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mMeshShader->SetMatrixUniform("uViewMatrix", mViewMatrix);
	// Construct projection matrix
	mProjectionMatrix = Matrix4::CreatePerspectiveFOV(
		Math::ToRadians(75.0f), 
		mWindowWidth,
		mWindowHeight, 
		25.0f, 
		10000.0f
	);
	mMeshShader->SetMatrixUniform("uProjectionMatrix", mProjectionMatrix);
	this->SetLightUniforms(mMeshShader);
	// =========== END MESH SHADER ================

	return true;
}

void Renderer::InitSpriteVertices()
{
	// Vertex buffer
	float vertices[] = {
		// Position		    //Normal			// Texel - invert the V coordinate
	   -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f,  0.0f, // top-left
		0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,	 // top-right
		0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  1.0f,  1.0f,  // bottom-right
	   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f// bottom-left
	};
	std::uint32_t indicies[] = {
		0, 1, 2, // First triangle
		2, 3, 0, // Second triangle
	};
	mSpriteVertices = new VertexArray(vertices, sizeof(vertices) / sizeof(float),
		indicies, sizeof(indicies) / sizeof(std::uint32_t));
}
