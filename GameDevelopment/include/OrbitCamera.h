#pragma once

#include"include/CameraComponent.h"

class OrbitCamera : public CameraComponent
{
public:
	OrbitCamera(class GameObject* owner, int updateOrder = 100, const std::string& name = "OrbitCamera");
	~OrbitCamera();
	virtual void Update(float deltaTime) override;
private:
	Vector3 mUp, mOffset;
	float mYawSpeed, mPitchSpeed;
};
