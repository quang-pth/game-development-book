#include "include/FPSGameObject.h"
#include "include/Game.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/AudioComponent.h"
#include "include/AudioSystem.h"
#include "include/FPSModel.h"
#include "include/FPSCameraComponent.h"
#include "include/FollowCamera.h"
#include "include/OrbitCamera.h"
#include "include/SplineCamera.h"
#include <iostream>

FPSGameObject::FPSGameObject(Game* game, const std::string& name) :
	GameObject(game, name), 
	mTarget(Vector3::UnitX), mWorldUp(Vector3::UnitZ),
	mOffset(Vector3::Zero),
	mLastFootStep(0.5f), mFPSModel(nullptr), 
	mCurrentCamera(nullptr), mCameras()
{
	mInputComponent = new InputComponent(this);
	mAudioComponent = new AudioComponent(this);

	std::shared_ptr<FollowCamera> followCamera = std::make_shared<FollowCamera>(this);
	followCamera->SetIsActive(false);
	std::shared_ptr<OrbitCamera> orbitCamera = std::make_shared<OrbitCamera>(this);
	orbitCamera->SetIsActive(false);
	mCameras.insert({ CameraComponent::State::EFPS, std::make_shared<FPSCamera>(this) });
	mCameras.insert({ CameraComponent::State::EFollow, followCamera});
	mCameras.insert({ CameraComponent::State::EOrbit, orbitCamera });
	
	this->ChangeCamera(CameraComponent::State::EFPS);

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
		Quaternion(GameObject::GetRight(), mCurrentCamera->GetPitchAngle()));
	mFPSModel->GetTransform()->SetRotation(rotation);

	mLastFootStep -= deltaTime;
	if (!Math::NearZero(mInputComponent->IsMoving()) && mLastFootStep < 0.0f) {
		mFootStep.SetPaused(false);
		mFootStep.Restart();
		mLastFootStep = 0.5f;
	}
}

void FPSGameObject::ProcessGameObjectInput(const InputState& inputState)
{
	if (inputState.KeyBoard.GetKeyState(SDL_SCANCODE_1) == ButtonState::EPressed) {
		this->ChangeCamera(CameraComponent::State::EFPS);
	}
	else if (inputState.KeyBoard.GetKeyState(SDL_SCANCODE_2) == ButtonState::EPressed) {
		this->ChangeCamera(CameraComponent::State::EFollow);
	}
	else if (inputState.KeyBoard.GetKeyState(SDL_SCANCODE_3) == ButtonState::EPressed) {
		this->ChangeCamera(CameraComponent::State::EOrbit);
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

void FPSGameObject::ChangeCamera(CameraComponent::State state)
{
	if (mCurrentCamera) {
		if (state == mCurrentCamera->GetState()) 
			return;
		mCurrentCamera->OnExit();
	}

	mCurrentCamera = mCameras.at(state);
	mCurrentCamera->OnEnter();
}
