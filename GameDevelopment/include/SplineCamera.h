#pragma once

#include"include/CameraComponent.h"
#include"include/Spline.h"

class SplineCamera : public CameraComponent
{
public:
	SplineCamera(class GameObject* owner, int updateOrder = 100, const std::string& name = "SplineCamera");
	~SplineCamera();
	virtual void Update(float deltaTime) override;
	virtual const Matrix4& GetViewMatrix() const override { return mViewMatrix; }
	void Restart();
	const Spline& GetSpline() const { return mPath; }
	void SetSpline(const Spline& spline) { mPath = spline; }
	const bool& GetPaused() const { mPaused; }
	void SetPaused(bool paused) { mPaused = paused; }
private:
	Matrix4 mViewMatrix;
	bool mPaused;
	float mT;
	float mSpeed;
	size_t mIdx;
	Spline mPath;
	std::int8_t mDirectionFactor;
};

