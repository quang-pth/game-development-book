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
	void SetForwardSpeed(float speed);
	void SetAngularSpeed(float speed);
	void AddForce(const Vector3& force, ForceMode forceMode = ForceMode::Impulse);
	void ResetForce();
protected:
	float mForwardSpeed; // Velocity measured in units/second
	float mAngularSpeed; // Rotation angle measured in radians/second
	// Newtonian Physics
	float mMass;
	Vector3 mVelocity;
	Vector3 mSumOfForces;
	ForceMode mForceMode;
};

