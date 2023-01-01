#pragma once

#include"include/CameraComponent.h"

class OrbitCamera : public CameraComponent
{
public:
	OrbitCamera(class GameObject* owner, int updateOrder = 100, const std::string& name = "OrbitCamera");
	~OrbitCamera();
	virtual void Update(float deltaTime) override;
	virtual const Matrix4& GetViewMatrix() const override { return mViewMatrix; }
	float GetYawSpeed() const { return mYawSpeed; }
	float GetPitchSpeed() const { return mPitchSpeed; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
	void SetPitchSpeed(float speed) { mPitchSpeed= speed; }
private:
	Matrix4 mViewMatrix;
	Vector3 mUp, mOffset;
	float mYawSpeed, mPitchSpeed;
};
