#pragma once

#include<string>
#include<unordered_map>
#include<SDL2/SDL.h>
#include <GL/glew.h>

class Renderer
{
public:
	Renderer();
	~Renderer();
	bool Intialize(float screenWidth, float screenHeight);
	void ShutDown();
	void Unload();
	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);
private:
	bool LoadShaders();
	void InitSpriteVertices();
private:
	class Shader* mSpriteShader;
	class VertexArray* mSpriteVertices;
	std::vector<class SpriteComponent*> mSprites;
	std::unordered_map<std::string, class Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshes;
private:
	GLboolean mGlewExperimental;
	float mWindowWidth, mWindowHeight;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
};

