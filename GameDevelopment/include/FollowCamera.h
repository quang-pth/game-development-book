#pragma once

#include"include/CameraComponent.h"
#include"include/CustomMath.h"

class FollowCamera : public CameraComponent
{
public:
	FollowCamera(class GameObject* owner, int updateOrder = 101, const std::string& name = "FollowCamera");
	~FollowCamera();
	virtual void Update(float deltaTime) override;
	void SetHDist(float dist) { mHDist = dist; }
	void SetVDist(float dist) { mVDist = dist; }
	void SetTargetDist(float dist) { mTargetDist = dist; }
	float GetHDist() const { return mHDist; }
	float GetVDist() const { return mVDist; }
	float GetTargetDist() const { return mTargetDist; }
private:
	Vector3 ComputeCameraPosition() const;
	void UpdateActualCameraPosition(float deltaTime);
	void SnapToIdeal();
	void FollowTarget();
private:
	Vector3 mActualPos, mVelocity;
	float mHDist, mVDist, mTargetDist;
	float mSpringConstant;
};