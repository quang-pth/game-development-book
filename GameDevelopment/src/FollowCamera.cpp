#include "include/FollowCamera.h"
#include "include/Game.h"
#include "include/InputSystem.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"
#include <iostream>

FollowCamera::FollowCamera(GameObject* owner, int updateOrder, const std::string& name) :
	CameraComponent(owner, updateOrder, name),
	mOffset(-400.0f, 0.0f, 350.0f), mTargetDist(100.0f),
	mSpringConstant(8.0f), mYawSpeed(0.0f), mPitchSpeed(0.0f), 
	mUp(Vector3::UnitZ)
{
	this->SnapToIdeal();
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	this->UpdateActualCameraPosition(deltaTime);
	this->FollowTarget(deltaTime);
}

void FollowCamera::ProcessInput(const InputState& inputState)
{
	mYawSpeed = 0.0f;
	mPitchSpeed = 0.0f;

	RelativeMouse mouseInfo = mOwner->GetGame()->GetInputSystem()->GetRelativeMouse();
	if (mouseInfo.Buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		static int maxMouseSpeed = 500;
		static float maxOrbitSpeed = Math::Pi * 8;

		if (mouseInfo.Position.x != 0)
		{
			// Convert to ~[-1.0, 1.0]
			mYawSpeed = static_cast<float>(mouseInfo.Position.x) / maxMouseSpeed;
			// Multiply by rotation/sec
			mYawSpeed *= maxOrbitSpeed;
		}

		if (mouseInfo.Position.y != 0)
		{
			mPitchSpeed = static_cast<float>(mouseInfo.Position.y) / maxMouseSpeed;
			mPitchSpeed *= maxOrbitSpeed;
		}

		mUp = mOwner->GetUp();
	}
	else {
		mUp = Vector3::UnitZ;
		mOffset = Vector3(-400.0f, 0.0f, 350.0f);
	}
}

Vector3 FollowCamera::ComputeCameraPosition() const
{
	Vector3 position = mOwner->GetTransform()->GetPosition() + mOwner->GetForward() * mOffset.x;
	position += mUp * mOffset.z;
	position += mOwner->GetRight() * mOffset.y;
	return position;
}

void FollowCamera::UpdateActualCameraPosition(float deltaTime)
{
	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	const Vector3& idealPos = this->ComputeCameraPosition();
	const Vector3& diff = mActualPos - idealPos;
	const Vector3& acceleration = -mSpringConstant * diff - dampening * mVelocity;
	mVelocity += acceleration * deltaTime;
	mActualPos += mVelocity;
}

void FollowCamera::SnapToIdeal()
{
	mVelocity = Vector3::Zero;
	mActualPos = this->ComputeCameraPosition();
	this->FollowTarget();
}

void FollowCamera::FollowTarget(float deltaTime)
{
	// Yaw rotation
	Quaternion yaw(Vector3::UnitZ, mYawSpeed * deltaTime);
	mUp = Vector3::Transform(mUp, yaw);
	mOffset = Vector3::Transform(mOffset, yaw);
	// Pitch rotation
	const Vector3& forward = mOwner->GetTransform()->GetPosition() - this->ComputeCameraPosition();
	const Vector3& right = mUp.Cross(forward.Normalize());
	Quaternion pitch(right, mPitchSpeed * deltaTime);
	mUp = Vector3::Transform(mUp, pitch);
	mOffset = Vector3::Transform(mOffset, pitch);
	// Compute view matrix
	const Vector3& target = mOwner->GetTransform()->GetPosition() + mOwner->GetForward() * mTargetDist;
	mViewMatrix = Matrix4::CreateLookAt(mActualPos, target, mUp);
	CameraComponent::SetViewMatrix(mViewMatrix);
}