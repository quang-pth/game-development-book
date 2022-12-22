#include "include/Camera.h"
#include "include/Game.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/AudioComponent.h"
#include "include/AudioSystem.h"
#include <iostream>

Camera::Camera(Game* game, const std::string& name) :
	GameObject(game, name), 
	mOffset(Vector3::Zero),
	mTarget(Vector3::UnitX), mWorldUp(Vector3::UnitZ),
	mLastFootStep(0.5f)
{
	mInputComponent = new InputComponent(this);
	mAudioComponent = new AudioComponent(this);
	mFPSCameraComponent = new FPSCameraComponent(this);

	mFootStep = mAudioComponent->PlayEvent("event:/Footstep");
	mFootStep.SetPaused(true);
}

Camera::~Camera()
{
}

void Camera::UpdateGameObject(float deltaTime)
{
	GameObject::UpdateGameObject(deltaTime);

	mLastFootStep -= deltaTime;
	if (!Math::NearZero(mInputComponent->IsMoving()) && mLastFootStep < 0.0f) {
		mFootStep.SetPaused(false);
		mFootStep.Restart();
		mLastFootStep = 0.5f;
	}
}

void Camera::ProcessGameObjectInput(const InputState& inputState)
{
	GameObject::ProcessGameObjectInput(inputState);
}

void Camera::SetFootstepSurface(float value)
{
	mFootStep.SetPaused(true);
	mFootStep.SetParameter("Surface", value);
}