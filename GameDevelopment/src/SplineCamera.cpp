#include "include/SplineCamera.h"
#include "include/GameObject.h"
#include "include/TransformComponent.h"

SplineCamera::SplineCamera(GameObject* owner, int updateOrder, const std::string& name) :
	CameraComponent(owner, updateOrder, name),
	mPaused(false), mT(0.0f), mSpeed(0.3f),
	mIdx(1), mPath(), mDirectionFactor(1)
{
	mState = CameraComponent::State::ESpline;
}

SplineCamera::~SplineCamera()
{
}

void SplineCamera::Update(float deltaTime)
{
	if (mPaused) return;

	CameraComponent::Update(deltaTime);

	mT += mSpeed * deltaTime;

	if (mT > 1.0f) {
		mIdx += 1;
		mT -= 1.0f;
	}

	if (mIdx > mPath.GetNumPoints() - 4) {
		mPath.ReversePath();
		mDirectionFactor *= -1;
		this->Restart();
		return;
	}

	const Vector3& cameraPosition = mPath.ComputePosition(mIdx, mT);
	const Vector3& target = mPath.ComputePosition(mIdx, mT + 0.001f * mDirectionFactor);
	mViewMatrix = Matrix4::CreateLookAt(cameraPosition, target, Vector3::UnitZ);
	CameraComponent::SetViewMatrix(mViewMatrix);
}

void SplineCamera::OnEnter()
{
}

void SplineCamera::OnExit()
{
}

void SplineCamera::Restart()
{
	mIdx = 1;
	mT = 0.0f;
	mPaused = false;
}