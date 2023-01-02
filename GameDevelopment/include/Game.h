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
	void SetIsRunning(bool isRunning);
	class FPSGameObject* GetFPSGameObject() const;
	class Renderer* GetRenderer() const;
	class AudioSystem* GetAudioSystem() const;
	class InputSystem* GetInputSystem() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
private:
	void ProcessInput();
	void HandlKeyPress(std::uint32_t key);
	void UpdateGame();
	void ChangeCamera(int mode);
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
	class GameObject* mCrosshair;
	class FPSGameObject* mFPSGameObject;
	class FollowGameObject* mFollowGameObject;
	class OrbitGameObject* mOrbitGameObject;
	class SplineGameObject* mSplineGameObject;
	class GameObject* mStartPoint;
	class GameObject* mEndPoint;
	// System
	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;
	class InputSystem* mInputSystem;
	SoundEvent mMusicEvent;
	SoundEvent mReverbSnap;
	// Thread control
	bool mUpdatingGameObjects;
};
