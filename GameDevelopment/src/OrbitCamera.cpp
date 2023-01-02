#include "include/OrbitCamera.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"

OrbitCamera::OrbitCamera(GameObject* owner, int updateOrder, const std::string& name) :
	CameraComponent(owner, updateOrder, name),
	mUp(Vector3::UnitZ), mOffset(Vector3(-400.0f, 0.0f, 0.0f)),
	mYawSpeed(0.0f), mPitchSpeed(0.0f)
{
}

OrbitCamera::~OrbitCamera()
{
}

void OrbitCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	// Yaw rotation
	Quaternion yaw = Quaternion(Vector3::UnitZ, mYawSpeed * deltaTime);
	mOffset = Vector3::Transform(mOffset, yaw);
	mUp = Vector3::Transform(mUp, yaw);

	// forward = onwer.position - (owner.position + camera.offset)
	const Vector3& forward = (-1.0f * mOffset);
	const Vector3& right = mUp.Cross(forward).Normalize();

	// Pitch rotation
	Quaternion pitch = Quaternion(right, mPitchSpeed * deltaTime);
	mOffset = Vector3::Transform(mOffset, pitch);
	mUp = Vector3::Transform(mUp, pitch);

	// Set orbit view
	const Vector3& targetPosition = mOwner->GetTransform()->GetPosition();
	const Vector3& cameraPosition = targetPosition + mOffset;
	mViewMatrix = Matrix4::CreateLookAt(cameraPosition, targetPosition, mUp);
	CameraComponent::SetViewMatrix(mViewMatrix);
}
