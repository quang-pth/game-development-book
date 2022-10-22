#pragma once

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
	SDL_Texture* GetTexture(const std::string& fileName);
	int GetWindowWidth() const { return mWindowWidth; }
	int GetWindowHeight() const { return mWindowHeight; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	// Game Window
	SDL_Window* mWindow;
	int mWindowWidth;
	int mWindowHeight;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	float mTicksCount; // Measured in miliseconds
	// Game Objects
	std::vector<class GameObject*> mGameObjects;
	std::vector<class GameObject*> mPendingGameObjects;
	bool mUpdatingGameObjects;
	class Mario* mShip;
	// Sprites
	std::vector<class SpriteComponent*> mSprites;
	std::unordered_map<std::string, SDL_Texture*> mTextures;
};
