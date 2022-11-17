#pragma once

#include<include/Component.h>
#include"include/CustomMath.h"
#include"include/Mario.h"

class MoveComponent : public Component
{
public:
	enum class ForceMode {
		Impulse,
		Constant,
	};

	MoveComponent() = default;
	MoveComponent(class GameObject* owner, int updateOrder = 10, std::string = "MoveComponent");

	void Update(float deltaTime) override;
	float GetForwardSpeed() const;
	Vector2 GetVelocity();
	void SetForwardSpeed(float speed);
	void AddForce(const Vector2& force, ForceMode forceMode = ForceMode::Impulse);
	void ResetForce();
	void ToggleHorizontalDirection(float speed);
	Direction GetDirection() const;
protected:
	float mForwardSpeed; // Velocity measured in units/second
	Direction mDirection;
	// Newtonian Physics
	float mMass;
	Vector2 mForceVelocity;
	Vector2 mSumOfForces;
	ForceMode mForceMode;
};

