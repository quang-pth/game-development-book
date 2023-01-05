#pragma once

#include"include/CameraComponent.h"

class FPSCamera : public CameraComponent
{
public:
	FPSCamera(class GameObject* owner, int updateOrder = 100, const std::string& name = "FPSCameraComponent");
	~FPSCamera();
	virtual void Update(float deltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	float GetMaxPitchSpeed() const { return mMaxPitchAngle; }
	void SetMaxPitchSpeed(float speed) { mMaxPitchAngle = speed; }
private:
	void ComputeViewMatrix();
private:
	float mMaxPitchAngle;
};
