#pragma once

#include"include/CameraComponent.h"

class FPSCameraComponent : public CameraComponent
{
public:
	FPSCameraComponent(class GameObject* owner, int updateOrder = 100, const std::string& name = "FPSCameraComponent");
	~FPSCameraComponent();
	virtual void Update(float deltaTime) override;
	virtual const Matrix4& GetViewMatrix() const override { return mViewMatrix; };
	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetMaxPitchSpeed() const { return mMaxPitchAngle; }
	float GetPitchAngle() const { return mPitchAngle; }
public:
	void SetPitchSpeed(float speed) { mPitchSpeed = speed; mRecomputeMatix = true; }
	void SetMaxPitchSpeed(float speed) { mMaxPitchAngle = speed; }
	void SetPitchAngle(float angle) { mPitchAngle = angle; }
private:
	void ComputeViewMatrix();
private:
	float mPitchSpeed;
	float mMaxPitchAngle;
	float mPitchAngle;
	bool mRecomputeMatix;
	Matrix4 mViewMatrix;
};

