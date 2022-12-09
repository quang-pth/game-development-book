#pragma once

#include<include/GameObject.h>
#include "include/SoundEvent.h"

class InputComponent;
class AudioComponent;

class Camera : public GameObject
{
public:
	Camera(class Game* game, const std::string& name = "Camera");
	~Camera();
	virtual void UpdateGameObject(float deltaTime) override;
	Matrix4 GetViewMatrix() const { return mViewMatrix; }
	InputComponent* GetInputComponent() const { return mInputComponent; }
	void SetFootstepSurface(float value);
private:
	void ComputeViewMatrix();
private:
	Matrix4 mViewMatrix;
	Vector3 mTarget, mWorldUp;
	Vector3 mOffset;
	SoundEvent mFootStep;
	InputComponent* mInputComponent;
	AudioComponent* mAudioComponent;
	float mLastFootStep;
	bool mRecomputeViewMatrix;
};

