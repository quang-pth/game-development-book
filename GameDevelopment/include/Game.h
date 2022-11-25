#pragma once

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<vector>
#include<unordered_map>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObject(class GameObject* gameObject);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	class Texture* GetTexture(const std::string& fileName);
	class std::vector<class Asteroid*> GetAsteroids() const;
	class Ship* GetShip() const;
	class CooldownManager* GetCooldownManager() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
private:
	bool LoadShaders();
	void InitSpriteVertices();
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
private:
	// Game Window
	SDL_Window* mWindow;
	int mWindowWidth;
	int mWindowHeight;
	SDL_GLContext mContext;
	class VertexArray* mSpriteVertices;
	GLboolean glewExperimental;
	class Shader* mSpriteShader;
	bool mIsRunning;
	float mTicksCount; // Measured in mili-seconds
	// Game Objects
	std::vector<class GameObject*> mGameObjects;
	std::vector<class GameObject*> mPendingGameObjects;
	std::vector<class Asteroid*> mAsteroids;
	class CooldownManager* mCooldownManager;
	class Ship* mShip;
	bool mUpdatingGameObjects;
	// Sprites
	std::vector<class SpriteComponent*> mSprites;
	std::unordered_map<std::string, class Texture*> mTextures;
};
