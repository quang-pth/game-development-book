#include "include/Camera.h"
#include "include/Game.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/AudioComponent.h"
#include "include/AudioSystem.h"
#include <iostream>

Camera::Camera(Game* game, const std::string& name) :
	GameObject(game, name), 
	mViewMatrix(Matrix4::Identity), mOffset(Vector3::Zero),
	mTarget(Vector3::UnitX), mWorldUp(Vector3::UnitZ),
	mRecomputeViewMatrix(true), mLastFootStep(0.5f)
{
	mInputComponent = new InputComponent(this);
	mAudioComponent = new AudioComponent(this);
	mFootStep = mAudioComponent->PlayEvent("event:/Footstep");
	mFootStep.SetPaused(true);

	// Compute third-person perspective camera
	this->ComputeViewMatrix();
}

Camera::~Camera()
{
}

void Camera::UpdateGameObject(float deltaTime)
{
	GameObject::UpdateGameObject(deltaTime);

	mLastFootStep -= deltaTime;
	if (!Math::NearZero(mInputComponent->GetForwardSpeed()) && mLastFootStep < 0.0f) {
		mFootStep.SetPaused(false);
		mFootStep.Restart();
		mLastFootStep = 0.5f;
	}
	
	this->ComputeViewMatrix();
}

void Camera::SetFootstepSurface(float value)
{
	mFootStep.SetPaused(true);
	mFootStep.SetParameter("Surface", value);
}

void Camera::ComputeViewMatrix()
{
	const Vector3& position = GameObject::GetTransform()->GetPosition();
	mTarget = position + GameObject::GetForward() * 50.0f;
	mViewMatrix = Matrix4::CreateLookAt(position, mTarget, mWorldUp);
	GameObject::GetGame()->GetAudioSystem()->SetListener(mViewMatrix, mOffset);
}
