#pragma once

#include"include/Component.h"
#include"include/CustomMath.h"

class CameraComponent : public Component
{
public:
	enum class State {
		EFPS,
		EFollow,
		EOrbit,
		ESpline
	};
	CameraComponent(class GameObject* owner, int updateOrder = 100, const std::string& name = "CameraComponent");
	virtual void Update(float deltaTime) override;
	virtual void OnEnter();
	virtual void OnExit();
	virtual ~CameraComponent();
	virtual const Matrix4& GetViewMatrix() const { return mViewMatrix; };
	void SetYawAngle(float angle) { mYawAngle = angle; mRecomputeMatix = true; }
	void SetPitchAngle(float angle) { mPitchAngle = angle; mRecomputeMatix = true; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; mRecomputeMatix = true; }
	void SetPitchSpeed(float speed) { mPitchSpeed = speed; mRecomputeMatix = true; }
	float GetYawAngle() const { return mYawAngle; }
	float GetPitchAngle() const { return mPitchAngle; }
	float GetYawSpeed() const { return mYawSpeed; }
	float GetPitchSpeed() const { return mPitchSpeed; }
	State GetState() const { return mState; }
protected:
	void SetViewMatrix(const Matrix4& viewMatrix);
protected:
	Matrix4 mViewMatrix;
	float mYawAngle, mPitchAngle;
	float mYawSpeed, mPitchSpeed;
	bool mRecomputeMatix;
	State mState;
};
