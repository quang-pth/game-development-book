#pragma once

#include<include/GameObject.h>

class Camera : public GameObject
{
public:
	Camera(class Game* game, const std::string& name = "Camera");
	~Camera();
	virtual void UpdateGameObject(float deltaTime) override;
	Matrix4 GetViewMatrix() const { return mViewMatrix; }
	class InputComponent* GetInputComponent() const { return mInputComponent; }
private:
	void ComputeViewMatrix();
private:
	Matrix4 mViewMatrix;
	Vector3 mTarget, mWorldUp;
	class InputComponent* mInputComponent;
	bool mRecomputeViewMatrix;
};

