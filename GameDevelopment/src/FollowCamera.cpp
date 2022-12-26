#include "include/FollowCamera.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"

FollowCamera::FollowCamera(GameObject* owner, int updateOrder, const std::string& name) :
	CameraComponent(owner, updateOrder, name),
	mHDist(200.0f), mVDist(50.0f), mTargetDist(60.0f),
	mSpringConstant(1.0f)
{
	this->SnapToIdeal();
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	const Vector3& idealPos = this->ComputeCameraPosition();
	const Vector3& diff = mActualPos - idealPos;
	const Vector3& acceleration = -mSpringConstant * diff - dampening * mVelocity;
	mVelocity += acceleration * deltaTime;
	mActualPos += mVelocity;

	this->SetFollow();
}

Vector3 FollowCamera::ComputeCameraPosition() const
{
	Vector3 position = mOwner->GetTransform()->GetPosition() - mOwner->GetForward() * mHDist;
	position += Vector3::UnitZ * mVDist;
	return position;
}

void FollowCamera::SnapToIdeal()
{
	mVelocity = Vector3::Zero;
	mActualPos = this->ComputeCameraPosition();
	this->SetFollow();
}

void FollowCamera::SetFollow()
{
	const Vector3& ownerPosition = mOwner->GetTransform()->GetPosition();
	const Vector3& target = ownerPosition + mOwner->GetForward() * mTargetDist;
	CameraComponent::SetViewMatrix(Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ));
}