#pragma once

#include<include/Component.h>
#include"include/CustomMath.h"

class MoveComponent : public Component
{
public:
	enum class ForceMode {
		Impulse,
		Constant,
	};

	MoveComponent() = default;
	MoveComponent(class GameObject* owner, int updateOrder = 10, std::string = "MoveComponent");

	virtual void Update(float deltaTime) override;
	virtual void OnUpdateWorldTransform() override;
	float GetForwardSpeed() const;
	float GetAngularSpeed() const;
	float GetStrafeSpeed() const;
	const Vector3& GetVelocity() const;
public:
	void SetForwardSpeed(float speed);
	void SetAngularSpeed(float speed);
	void SetStrafeSpeed(float speed);
	void SetVelocity(const Vector3& velocity);
protected:
	float mForwardSpeed; 
	float mStrafeSpeed;
	float mAngularSpeed; 
	Vector3 mVelocity;
};