#pragma once

#include<vector>
#include<unordered_map>
#include"include/SoundEvent.h"

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
	class AudioSystem* GetAudioSystem() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
private:
	void ProcessInput();
	void HandlKeyPress(std::uint32_t key);
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
	class Camera* mCamera;
	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;
	SoundEvent mMusicEvent;
	SoundEvent mReverbSnap;
	bool mUpdatingGameObjects;
};
