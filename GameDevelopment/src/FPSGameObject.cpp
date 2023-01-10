#include "include/FPSGameObject.h"
#include "include/Game.h"
#include "include/Collision.h"
#include "include/Renderer.h"
#include "include/Level.h"
#include "include/Decoration.h"
#include "include/Mesh.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/MeshComponent.h"
#include "include/BoxComponent.h"
#include "include/AudioComponent.h"
#include "include/AudioSystem.h"
#include "include/FPSModel.h"
#include "include/FPSCameraComponent.h"
#include "include/FollowCamera.h"
#include "include/OrbitCamera.h"
#include "include/SplineCamera.h"
#include <iostream>

const float MAX_COOLDOWN = 0.2f;

FPSGameObject::FPSGameObject(Game* game, const std::string& name) :
	GameObject(game, name), 
	mLastFootStep(0.5f), mFPSModel(nullptr), 
	mCurrentCamera(nullptr), mCameras(), mCooldown(MAX_COOLDOWN)
{
	mInputComponent = new InputComponent(this);
	mAudioComponent = new AudioComponent(this);

	mCameras.emplace_back(std::make_shared<FPSCamera>(this));
	std::shared_ptr<FollowCamera> followCamera = std::make_shared<FollowCamera>(this);
	followCamera->SetIsActive(false);
	mCameras.emplace_back(followCamera);
	this->ChangeCamera(CameraComponent::State::EFPS);

	// Init fire balls
	for (std::uint16_t i = 0; i < mBalls.size(); i++) {
		mBalls[i] = new Ball(game);
	}

	mFootStep = mAudioComponent->PlayEvent("event:/Footstep");
	mFootStep.SetPaused(true);
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

	mCooldown -= deltaTime;
}

void FPSGameObject::ProcessGameObjectInput(const InputState& inputState)
{
	if (mInputComponent->GetMappedActionState("FollowCamera")) {
		this->ChangeCamera(CameraComponent::State::EFollow);
	}
	else if (mInputComponent->GetMappedActionState("FPSCamera")) {
		this->ChangeCamera(CameraComponent::State::EFPS);
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

void FPSGameObject::Fire()
{
	if (mCooldown > 0.0f) return;
	else {
		mCooldown = MAX_COOLDOWN;
	}

	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = GameObject::GetGame()->GetRenderer()->Unproject(screenPoint);
	screenPoint.z = 0.95f;
	Vector3 end = GameObject::GetGame()->GetRenderer()->Unproject(screenPoint);
	Vector3 fireDirection = end - start;
	fireDirection.Normalized();
	// Fire ball
	for (std::uint32_t i = mPrevBallIdx; i < mBalls.size(); i++) {
		Ball* ball = mBalls[i];

		if (ball->GetState() == GameObject::State::EActive) continue;

		ball->Fire(start, fireDirection);

		break;
	}
	
	mPrevBallIdx++;
	if (mPrevBallIdx >= mBalls.size()) {
		mPrevBallIdx = 0;
	}
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

void FPSGameObject::FixCollisions()
{
	GameObject::GetTransform()->ComputeWorldTransform();
	Vector3 position = mFPSModel->GetTransform()->GetPosition();
	const AABB& fpsBox = mFPSModel->GetBoxComponent()->GetWorldBox();
	const std::vector<Decoration*>& planes = GameObject::GetGame()->GetLevel()->GetPlanes();

	for (auto plane : planes) {
		const AABB& planeBox = plane->GetBoxComponent()->GetWorldBox();
		if (Collision::Intersect(fpsBox, planeBox)) {
			float dx1 = planeBox.mMin.x - fpsBox.mMax.x;
			float dx2 = planeBox.mMax.x - fpsBox.mMin.x;
			float dy1 = planeBox.mMin.y - fpsBox.mMax.y;
			float dy2 = planeBox.mMax.y - fpsBox.mMin.y;
			float dz1 = planeBox.mMin.z - fpsBox.mMax.z;
			float dz2 = planeBox.mMax.z - fpsBox.mMin.z;

			float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
			float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
			float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;
			
			if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz)) 
			{
				position.x += dx;
			}
			else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz)) {
				position.y += dy;
			}
			else {
				position.z += dz;
			}
		}

		mFPSModel->GetTransform()->SetPosition(position);
		mFPSModel->GetBoxComponent()->OnUpdateWorldTransform();
	}
}
