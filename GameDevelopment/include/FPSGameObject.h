#pragma once

#include<include/GameObject.h>
#include "include/SoundEvent.h"
#include "include/InputSystem.h"
#include "include/FPSCameraComponent.h"

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
	Matrix4 GetViewMatrix() const { return mFPSCameraComponent->GetViewMatrix(); }
	InputComponent* GetInputComponent() const { return mInputComponent; }
	FPSCameraComponent* GetFPSCamera() const { return mFPSCameraComponent; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	float GetStrafeSpeed() const { return mStrafeSpeed; }
	void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
	void SetFootstepSurface(float value);
	void SetModel(FPSModel* model) { mFPSModel = model; };
private:
	Vector3 mTarget, mWorldUp;
	Vector3 mOffset;
	SoundEvent mFootStep;
	float mLastFootStep;
	float mForwardSpeed, mStrafeSpeed;
	InputComponent* mInputComponent;
	AudioComponent* mAudioComponent;
	FPSCameraComponent* mFPSCameraComponent;
	FPSModel* mFPSModel;
};

