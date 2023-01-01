#include "include/FPSGameObject.h"
#include "include/Game.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/AudioComponent.h"
#include "include/AudioSystem.h"
#include "include/FPSModel.h"
#include <iostream>

FPSGameObject::FPSGameObject(Game* game, const std::string& name) :
	GameObject(game, name), 
	mTarget(Vector3::UnitX), mWorldUp(Vector3::UnitZ),
	mOffset(Vector3::Zero),
	mLastFootStep(0.5f), mFPSModel(nullptr)
{
	mInputComponent = new InputComponent(this);
	mAudioComponent = new AudioComponent(this);
	mFPSCameraComponent = new FPSCameraComponent(this);

	mFootStep = mAudioComponent->PlayEvent("event:/Footstep");
	mFootStep.SetPaused(true);
}

FPSGameObject::~FPSGameObject()
{
}

void FPSGameObject::UpdateGameObject(float deltaTime)
{
	GameObject::UpdateGameObject(deltaTime);

	// Update FPS model position
	const Vector3 modelOffset(10.0f, 10.0f, -10.0f);
	Vector3 modelPosition = GameObject::GetTransform()->GetPosition();
	modelPosition += GameObject::GetForward() * modelOffset.x;
	modelPosition += GameObject::GetRight() * modelOffset.y;
	modelPosition += modelOffset;

	mFPSModel->GetTransform()->SetPosition(modelPosition);
	// Init FPS model to the FPS gameobject rotation
	Quaternion rotation = GameObject::GetTransform()->GetRotation();
	// Rotate the transform by camera pitch angle
	rotation = Quaternion::Concatenate(rotation, 
		Quaternion(GameObject::GetRight(), mFPSCameraComponent->GetPitchAngle()));
	mFPSModel->GetTransform()->SetRotation(rotation);

	mLastFootStep -= deltaTime;
	if (!Math::NearZero(mInputComponent->IsMoving()) && mLastFootStep < 0.0f) {
		mFootStep.SetPaused(false);
		mFootStep.Restart();
		mLastFootStep = 0.5f;
	}
}

void FPSGameObject::SetFootstepSurface(float value)
{
	mFootStep.SetPaused(true);
	mFootStep.SetParameter("Surface", value);
}

void FPSGameObject::SetVisible(bool visible)
{
	mFPSModel->SetVisible(visible);
}
