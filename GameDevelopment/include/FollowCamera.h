#pragma once

#include"include/CameraComponent.h"
#include"include/CustomMath.h"

class FollowCamera : public CameraComponent
{
public:
	FollowCamera(class GameObject* owner, int updateOrder = 101, const std::string& name = "FollowCamera");
	~FollowCamera();
	virtual void Update(float deltaTime) override;
	virtual const Matrix4& GetViewMatrix() const override { return mViewMatrix; };
	void SnapToIdeal();
	void SetHorizontalDist(float dist) { mHorizontalDist = dist; }
	void SetVerticalDist(float dist) { mVerticalDist = dist; }
	void SetTargetDist(float dist) { mTargetDist = dist; }
	float GetHorizontalDist() const { return mHorizontalDist; }
	float GetVerticalDist() const { return mVerticalDist; }
	float GetTargetDist() const { return mTargetDist; }
private:
	Vector3 ComputeCameraPosition() const;
	void UpdateActualCameraPosition(float deltaTime);
	void FollowTarget();
private:
	Matrix4 mViewMatrix;
	Vector3 mActualPos, mVelocity;
	float mHorizontalDist, mVerticalDist, mTargetDist;
	float mSpringConstant;
};