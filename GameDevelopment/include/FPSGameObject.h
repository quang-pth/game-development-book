#pragma once

#include<include/GameObject.h>
#include "include/SoundEvent.h"
#include "include/InputSystem.h"
#include "include/CameraComponent.h"
#include<unordered_map>
#include<memory>

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
	InputComponent* GetInputComponent() const { return mInputComponent; }
	const std::shared_ptr<CameraComponent>& GetCamera() const { return mCurrentCamera; }
	void SetFootstepSurface(float value);
	FPSModel* GetModel() const { return mFPSModel; }
	void SetModel(FPSModel* model) { mFPSModel = model; };
	void SetVisible(bool visible);
private:
	void ChangeCamera(CameraComponent::State state);
private:
	Vector3 mTarget, mWorldUp;
	Vector3 mOffset;
	SoundEvent mFootStep;
	float mLastFootStep;
	InputComponent* mInputComponent;
	AudioComponent* mAudioComponent;
	std::shared_ptr<CameraComponent> mCurrentCamera;
	std::unordered_map<CameraComponent::State, std::shared_ptr<CameraComponent>> mCameras;
	FPSModel* mFPSModel;
};

