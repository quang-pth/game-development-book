#pragma once

#include"include/CameraComponent.h"
#include"include/Spline.h"

class SplineCamera : public CameraComponent
{
public:
	SplineCamera(class GameObject* owner, int updateOrder = 100, const std::string& name = "SplineCamera");
	~SplineCamera();
	virtual void Update(float deltaTime) override;
private:
	bool mPaused;
	float mT;
	float mSpeed;
	size_t mIdx;
	Spline mPath;
};

