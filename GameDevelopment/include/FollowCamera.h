#pragma once

#include"include/CameraComponent.h"
#include"include/CustomMath.h"

class FollowCamera : public CameraComponent
{
public:
	FollowCamera(class GameObject* owner, int updateOrder = 101, const std::string& name = "FollowCamera");
	~FollowCamera();
	virtual void Update(float deltaTime) override;
	virtual void ProcessInput(const InputState& inputState) override;
	virtual const Matrix4& GetViewMatrix() const override { return mViewMatrix; };
	void SnapToIdeal();
	void SetTargetDist(float dist) { mTargetDist = dist; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	float GetTargetDist() const { return mTargetDist; }
	float GetYawSpeed() const { return mYawSpeed; }
	float GetPitchSpeed() const { return mPitchSpeed; }
private:
	Vector3 ComputeCameraPosition() const;
	void UpdateActualCameraPosition(float deltaTime = 0.0f);
	void FollowTarget(float deltaTime = 0.0f);
private:
	Matrix4 mViewMatrix;
	Vector3 mActualPos, mVelocity;
	Vector3 mUp, mOffset;
	float mTargetDist;
	float mSpringConstant;
	float mYawSpeed, mPitchSpeed;
};