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

	MoveComponent();
	MoveComponent(class GameObject* owner, int updateOrder = 10, std::string = "MoveComponent");

	void Update(float deltaTime) override;
	float GetForwardSpeed() const;
	float GetAngularSpeed() const;
	void SetForwardSpeed(float speed);
	void SetAngularSpeed(float speed);
	void AddForce(const Vector2& force, ForceMode forceMode = ForceMode::Impulse);
	void ResetForce();
protected:
	float mForwardSpeed; // Velocity measured in units/second
	float mAngularSpeed; // Rotation angle measured in radians/second
	// Newtonian Physics
	float mMass;
	Vector2 mForceVelocity;
	Vector2 mSumOfForces;
	ForceMode mForceMode;
};

