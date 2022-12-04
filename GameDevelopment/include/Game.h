#pragma once

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
	class Camera* GetCamera() const;
	class Renderer* GetRenderer() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
private:
	// Game Window
	int mWindowWidth;
	int mWindowHeight;
	bool mIsRunning;
	float mTicksCount; // Measured in mili-seconds
	// Game Objects
	std::vector<class GameObject*> mGameObjects;
	std::vector<class GameObject*> mPendingGameObjects;
	std::vector<class Asteroid*> mAsteroids;
	class CooldownManager* mCooldownManager;
	class Camera* mCamera;
	class Ship* mShip;
	class Renderer* mRenderer;
	bool mUpdatingGameObjects;
};
