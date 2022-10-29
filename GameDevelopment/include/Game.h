#pragma once

#include<SDL2/SDL.h>
#include<include/CustomMath.h>
#include<vector>
#include<unordered_map>
#include<memory>

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
	class Mario* GetMario() const;
	class TileMapComponent* GetTileMapComponent() const;
	class CooldownManager* GetCooldownManager() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	Vector2 GetCenterPoint() const;
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	// Game Window
	SDL_Window *mpWindow;
	int mWindowWidth;
	int mWindowHeight;
	SDL_Renderer *mpRenderer;
	bool mIsRunning;
	float mTicksCount; // Measured in miliseconds
	// Game Objects
	std::vector<class GameObject*> mpGameObjects;
	std::vector<class GameObject*> mpPendingGameObjects;
	class CooldownManager* mpCooldownManager;
	bool mpUpdatingGameObjects;
	class Mario *mpMario;
	class TileMapComponent *mpTilemap;
	class StateManager *mpStateManager;
	// Sprites
	std::vector<SpriteComponent*> mpSprites;
	std::unordered_map<std::string, SDL_Texture*> mpTextures;
};
