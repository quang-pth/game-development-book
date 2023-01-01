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
	InputComponent* GetInputComponent() const { return mInputComponent; }
	FPSCameraComponent* GetFPSCamera() const { return mFPSCameraComponent; }
	void SetFootstepSurface(float value);
	FPSModel* GetModel() const { return mFPSModel; }
	void SetModel(FPSModel* model) { mFPSModel = model; };
	void SetVisible(bool visible);
private:
	Vector3 mTarget, mWorldUp;
	Vector3 mOffset;
	SoundEvent mFootStep;
	float mLastFootStep;
	InputComponent* mInputComponent;
	AudioComponent* mAudioComponent;
	FPSCameraComponent* mFPSCameraComponent;
	FPSModel* mFPSModel;
};

