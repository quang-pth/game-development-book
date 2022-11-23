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
	void ToggleHorizontalDirection(float speed);
	Direction GetDirection() const;
	void SetDirection(Direction direction);
protected:
	float mForwardSpeed; // Velocity measured in units/second
	Direction mDirection;
};

