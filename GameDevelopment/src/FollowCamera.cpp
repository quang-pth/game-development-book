#include "include/FollowCamera.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"

FollowCamera::FollowCamera(GameObject* owner, int updateOrder, const std::string& name) :
	CameraComponent(owner, updateOrder, name),
	mHorizontalDist(300.0f), mVerticalDist(250.0f), mTargetDist(100.0f),
	mSpringConstant(64.0f)
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
	this->FollowTarget();
}

Vector3 FollowCamera::ComputeCameraPosition() const
{
	Vector3 position = mOwner->GetTransform()->GetPosition() - mOwner->GetForward() * mHorizontalDist;
	position += Vector3::UnitZ * mVerticalDist;
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

void FollowCamera::FollowTarget()
{
	const Vector3& ownerPosition = mOwner->GetTransform()->GetPosition();
	const Vector3& target = ownerPosition + mOwner->GetForward() * mTargetDist;
	mViewMatrix = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
	CameraComponent::SetViewMatrix(mViewMatrix);
}