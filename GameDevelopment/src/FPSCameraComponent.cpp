#include "include/FPSCameraComponent.h"
#include "include/TransformComponent.h"
#include "include/GameObject.h"

FPSCameraComponent::FPSCameraComponent(GameObject* owner, int updateOrder, const std::string& name) :
	CameraComponent(owner, updateOrder, name),
	mPitchSpeed(0.0f), 
	mMaxPitchAngle(Math::Pi * 0.3f), mPitchAngle(0.0f),
	mRecomputeMatix(true), mViewMatrix(Matrix4::Identity)
{
	this->ComputeViewMatrix();
}

FPSCameraComponent::~FPSCameraComponent()
{
}

void FPSCameraComponent::Update(float deltaTime)
{
	mPitchAngle += mPitchSpeed * deltaTime;
	mPitchAngle = Math::Clamp(mPitchAngle, -mMaxPitchAngle, mMaxPitchAngle);
	if (mPitchAngle != 0.0f) 
		mRecomputeMatix = true;

	this->ComputeViewMatrix();
}

void FPSCameraComponent::ComputeViewMatrix()
{
	if (mRecomputeMatix) {
		const Quaternion& pitchQuat = Quaternion(mOwner->GetRight(), mPitchAngle);

		const Vector3& up = Vector3::Transform(Vector3::UnitZ, pitchQuat);
		const Vector3& forwardTarget = Vector3::Transform(mOwner->GetForward(), pitchQuat);
		const Vector3& position = mOwner->GetTransform()->GetPosition();

		mViewMatrix = Matrix4::CreateLookAt(position, position + forwardTarget * 100.0f, up);
		CameraComponent::SetViewMatrix(mViewMatrix);

		mRecomputeMatix = false;
	}
}
