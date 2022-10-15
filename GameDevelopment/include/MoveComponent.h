#pragma once

#include<include/Component.h>

class MoveComponent : public Component
{
public:
	MoveComponent();
	MoveComponent(class GameObject* owner, int updateOrder = 10);

	void Update(float deltaTime) override;
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetAngularSpeed() const { return mAngularSpeed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
protected:
	// Velocity measured in units/second
	float mForwardSpeed;
	// Rotation angle measured in radians/second
	float mAngularSpeed;
};

