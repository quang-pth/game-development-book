#include "include/FPSGameObject.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/Mesh.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/MeshComponent.h"
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

	mCameras.emplace_back(std::make_shared<FPSCamera>(this));
	std::shared_ptr<FollowCamera> followCamera = std::make_shared<FollowCamera>(this);
	followCamera->SetIsActive(false);
	mCameras.emplace_back(followCamera);
	this->ChangeCamera(CameraComponent::State::EFPS);

	mFootStep = mAudioComponent->PlayEvent("event:/Footstep");
	mFootStep.SetPaused(true);

	mStartPoint = new GameObject(game);
	mStartPoint->GetTransform()->SetPosition(Vector3(25.0f, 10.0f, 0.0f));
	mStartPoint->GetTransform()->SetScale(1.5f);
	mStartPoint->GetTransform()->SetRotation(Quaternion(Vector3::UnitX, 180.0f));
	MeshComponent* mesh = new MeshComponent(mStartPoint);
	mesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter6/Cube.gpmesh"));
	
	mEndPoint = new GameObject(game);
	mEndPoint->GetTransform()->SetPosition(Vector3(25.0f, 10.0f, 0.0f));
	mEndPoint->GetTransform()->SetScale(1.5f);
	mEndPoint->GetTransform()->SetRotation(Quaternion(Vector3::UnitX, 180.0f));
	mesh = new MeshComponent(mEndPoint);
	mesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter6/Cube.gpmesh"));
}

FPSGameObject::~FPSGameObject()
{
}

void FPSGameObject::UpdateGameObject(float deltaTime)
{
	GameObject::UpdateGameObject(deltaTime);

	if (mCurrentCamera->GetState() == CameraComponent::State::EFPS) {
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
	}

	mLastFootStep -= deltaTime;
	if (!Math::NearZero(mInputComponent->IsMoving()) && mLastFootStep < 0.0f) {
		mFootStep.SetPaused(false);
		mFootStep.Restart();
		mLastFootStep = 0.5f;
	}
}

void FPSGameObject::ProcessGameObjectInput(const InputState& inputState)
{
	if (mInputComponent->GetMappedActionState("FollowCamera")) {
		this->ChangeCamera(CameraComponent::State::EFollow);
	}
	else if (mInputComponent->GetMappedActionState("FPSCamera")) {
		this->ChangeCamera(CameraComponent::State::EFPS);
	}
	if (mInputComponent->GetMappedActionValue("Fire")) {
		Vector3 screenPoint(0.0f, 0.0f, 0.0f);
		Vector3 start = GameObject::GetGame()->GetRenderer()->Unproject(screenPoint);
		screenPoint.z = 0.95f;
		Vector3 end = GameObject::GetGame()->GetRenderer()->Unproject(screenPoint);
		mStartPoint->GetTransform()->SetPosition(start);
		mEndPoint->GetTransform()->SetPosition(end);
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

	auto iter = std::find_if(mCameras.begin(), mCameras.end(), [&](const std::shared_ptr<CameraComponent>& camera) {
		return camera->GetState() == state;
	});
	mCurrentCamera = *iter;
	mCurrentCamera->OnEnter();
}
