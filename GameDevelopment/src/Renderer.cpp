#include "include/Renderer.h"
#include "include/Game.h"

#include "include/TransformComponent.h"
#include "include/SpriteComponent.h"
#include "include/MeshComponent.h"

#include "include/Camera.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/VertexArray.h"
#include "include/Mesh.h"

#include <SDL2/SDL_image.h>

Renderer::Renderer(Game* game) :
	mGame(game),
	mSpriteShader(nullptr),
	mShaderMap(), mMeshMap(),
	mSpriteVertices(nullptr),
	mSprites(), mLoadedTextures(), mLoadedMeshes(),
	mGlewExperimental(GL_FALSE),
	mWindowWidth(0.0f), mWindowHeight(0.0f),
	mWindow(), mContext(), mCamera(nullptr),
	mAmbientLight(Vector3(.3f, .3f, .3f))
{
	mDirectionalLight.mDirection = Vector3(0, -.7f, -.7f);
	mDirectionalLight.mDiffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	mDirectionalLight.mSpecularColor = Vector3(0.70f, 0.65f, .6f);
}

Renderer::~Renderer()
{
}

bool Renderer::Intialize(float screenWidth, float screenHeight)
{
	mWindowWidth = screenWidth;
	mWindowHeight = screenHeight;
	// Construct Projection matrix
	mProjectionMatrix = Matrix4::CreatePerspectiveFOV(
		Math::ToRadians(75.0f),
		mWindowWidth,
		mWindowHeight,
		25.0f,
		10000.0f
	);

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

	for (std::pair<const std::string&, Shader*> iter : mShaderMap) {
		iter.second->Unload();
		delete iter.second;
	}
	mShaderMap.clear();
}

void Renderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ============= MESH SHADER  =================
	glEnable(GL_DEPTH_TEST);
	for (std::pair<const std::string&, Shader*> shaderMapIter : mShaderMap) {
		shaderMapIter.second->SetActive();
		shaderMapIter.second->SetUniforms(this);
		// Render meshes that use the current-bounded shader
		for (MeshComponent*  mesh : mMeshMap[shaderMapIter.first]) 
		{
			mesh->Draw(shaderMapIter.second);
		}
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
	Matrix4 cameraView = mCamera->GetViewMatrix();
	cameraView.Invert();

	shader->SetActive();
	shader->SetVec3Uniform("uCameraPos", cameraView.GetTranslation());
	shader->SetVec3Uniform("uAmbientLight", mAmbientLight);
	shader->SetVec3Uniform("uDirLight.mDirection", mDirectionalLight.mDirection);
	shader->SetVec3Uniform("uDirLight.mDiffuseColor", mDirectionalLight.mDiffuseColor);
	shader->SetVec3Uniform("uDirLight.mSpecularColor", mDirectionalLight.mSpecularColor);
}

bool Renderer::BeginScene(Camera* camera)
{
	mCamera = camera;

	this->InitSpriteVertices();
	if (!this->LoadShaders()) {
		return false;
	}

	return true;
}

void Renderer::AddMesh(MeshComponent* mesh)
{
	// ============== INSERT SHADER TO SHADER MAP
	const std::string& name = mesh->GetMesh()->GetShaderName();
	auto shaderMapIter = mShaderMap.find(name);
	if (shaderMapIter == mShaderMap.end()) {
		mShaderMap.insert({ name, mesh->GetMesh()->GetShader() });
	}
	// ============== INSERT MESH TO MESH MAP
	auto meshMapIter = mMeshMap.find(name);
	if (meshMapIter == mMeshMap.end()) {
		mMeshMap.insert({ name, std::vector<MeshComponent*>() });
	}
	mMeshMap.find(name)->second.emplace_back(mesh);
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

void Renderer::RemoveMesh(MeshComponent* mesh)
{
	std::vector<MeshComponent*> meshComponents = mMeshMap.find(mesh->GetMesh()->GetShaderName())->second;
	auto iter = std::find(meshComponents.begin(), meshComponents.end(), mesh);
	if (iter != meshComponents.end()) {
		meshComponents.erase(iter);
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

Game* Renderer::GetGame() const
{
	return mGame;
}

const Matrix4& Renderer::GetViewMatrix() const
{
	return mViewMatrix;
}

const Matrix4& Renderer::GetProjectionMatrix() const
{
	return mProjectionMatrix;
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
	mSpriteShader->SetMatrix4Uniform("uViewProj", viewProj);
	// =========== END SPRITE SHADER ================
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
