#pragma once

#include<string>
#include<unordered_map>
#include<SDL2/SDL.h>
#include <GL/glew.h>
#include"include/CustomMath.h"

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();
	bool Intialize(float screenWidth, float screenHeight);
	void ShutDown();
	void Unload();
	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void AddMesh(class MeshComponent* mesh);
	void RemoveMesh(class MeshComponent* mesh);
	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);
private:
	bool LoadShaders();
	void InitSpriteVertices();
private:
	class Game* mGame;
	class Shader* mSpriteShader;
	class Shader* mMeshShader;
	class GameObject* mCamera;
	Matrix4 mViewMatrix;
	Matrix4 mProjectionMatrix;
	class VertexArray* mSpriteVertices;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class MeshComponent*> mMeshes;
	std::unordered_map<std::string, class Texture*> mLoadedTextures;
	std::unordered_map<std::string, class Mesh*> mLoadedMeshes;
private:
	GLboolean mGlewExperimental;
	float mWindowWidth, mWindowHeight;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
};

