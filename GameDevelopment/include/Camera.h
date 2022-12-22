#pragma once

#include<include/GameObject.h>
#include "include/SoundEvent.h"
#include "include/InputSystem.h"
#include "include/FPSCameraComponent.h"

class InputComponent;
class AudioComponent;

class Camera : public GameObject
{
public:
	Camera(class Game* game, const std::string& name = "Camera");
	~Camera();
	virtual void UpdateGameObject(float deltaTime) override;
	virtual void ProcessGameObjectInput(const InputState& inputState) override;
	Matrix4 GetViewMatrix() const { return mFPSCameraComponent->GetViewMatrix(); }
	InputComponent* GetInputComponent() const { return mInputComponent; }
	FPSCameraComponent* GetFPSCamera() const { return mFPSCameraComponent; }
	void SetFootstepSurface(float value);
private:
	Vector3 mTarget, mWorldUp;
	Vector3 mOffset;
	SoundEvent mFootStep;
	InputComponent* mInputComponent;
	AudioComponent* mAudioComponent;
	FPSCameraComponent* mFPSCameraComponent;
	float mLastFootStep;
};

