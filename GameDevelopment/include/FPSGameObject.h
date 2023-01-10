#pragma once

#include"include/GameObject.h"
#include"include/Ball.h"
#include"include/SoundEvent.h"
#include"include/InputSystem.h"
#include"include/CameraComponent.h"
#include<vector>
#include<memory>
#include<array>

class InputComponent;
class AudioComponent;
class FPSModel;

class FPSGameObject : public GameObject
{
public:
	FPSGameObject(class Game* game, const std::string& name = "Camera");
	~FPSGameObject();
	virtual void UpdateGameObject(float deltaTime) override;
	virtual void ProcessGameObjectInput(const InputState& inputState) override;
	void SetFootstepSurface(float value);
	void SetModel(FPSModel* model) { mFPSModel = model; };
	void SetVisible(bool visible);
	void Fire();
	InputComponent* GetInputComponent() const { return mInputComponent; }
	const std::shared_ptr<CameraComponent>& GetCamera() const { return mCurrentCamera; }
	FPSModel* GetModel() const { return mFPSModel; }
private:
	void ChangeCamera(CameraComponent::State state);
	void FixCollisions();
private:
	SoundEvent mFootStep;
	float mLastFootStep;
	InputComponent* mInputComponent;
	AudioComponent* mAudioComponent;
	std::shared_ptr<CameraComponent> mCurrentCamera;
	std::vector<std::shared_ptr<CameraComponent>> mCameras;
	FPSModel* mFPSModel;
	// Balls
	float mCooldown = 0.5f;
	std::uint32_t mPrevBallIdx;
	std::array<Ball*, 30> mBalls;
};

