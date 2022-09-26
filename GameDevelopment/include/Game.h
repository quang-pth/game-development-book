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
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	SDL_Texture* GetTexture(const std::string& fileName);
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
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	bool mUpdatingActors;
	class Ship* mShip;
	// Sprites
	std::vector<class SpriteComponent*> mSprites;
	std::unordered_map<std::string, SDL_Texture*> mTextures;
};
