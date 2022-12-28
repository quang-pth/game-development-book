#pragma once

#include<string>
#include<unordered_map>
#include<SDL2/SDL.h>
#include <GL/glew.h>
#include"include/CustomMath.h"

struct DirectionalLight {
	Vector3 mDirection;
	Vector3 mDiffuseColor;
	Vector3 mSpecularColor;
};

struct PointLight {
	Vector3 mPosition;
	Vector3 mAmbient;
	Vector3 mDiffuseColor;
	Vector3 mSpecularColor;
	float mSpecularPower;
	float mConstant;
	float mLinear;
	float mQuadratic;
};

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();
	bool Intialize(float screenWidth, float screenHeight);
	void ShutDown();
	bool BeginScene();
	void Unload();
	void Draw();
	void SetLightUniforms(class Shader* shader);
	void AddMesh(class MeshComponent* meshComponent);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void RemoveMesh(class MeshComponent* mesh);
	void SetViewMatrix(const Matrix4& matrix);
	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);
	class Game* GetGame() const;
	const Matrix4& GetViewMatrix() const;
	const Matrix4& GetProjectionMatrix() const;
	SDL_Window* GetWindow() const { return mWindow; }
	Vector3 Unproject(const Vector3& screenPoint) const;
	Vector3 GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
private:
	bool LoadShaders();
	void InitSpriteVertices();
	void InitDirectionalLight();
	void InitPointLights();
private:
	class Game* mGame;
	class Shader* mSpriteShader;
	std::unordered_map<std::string, class Shader*> mShaderMap;
	std::unordered_map<std::string, std::vector<class MeshComponent*>> mMeshMap;
	Matrix4 mViewMatrix;
	Matrix4 mProjectionMatrix;
	class VertexArray* mSpriteVertices;
	std::vector<class SpriteComponent*> mSprites;
	std::unordered_map<std::string, class Texture*> mLoadedTextures;
	std::unordered_map<std::string, class Mesh*> mLoadedMeshes;
private:
	/*================LIGHTING===================*/
	Vector3 mAmbientLight;
	DirectionalLight mDirectionalLight;
	PointLight mPointLights[4];
	/*================LIGHTING===================*/
private:
	GLboolean mGlewExperimental;
	float mWindowWidth, mWindowHeight;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
};

