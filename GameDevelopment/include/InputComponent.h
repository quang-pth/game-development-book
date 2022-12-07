#pragma once
#include "include/MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent();
	InputComponent(class GameObject* owner, int updateOrder = 4);
	~InputComponent();
	void ProcessInput(const uint8_t* keyState) override;
	float GetMaxForwardSpeed() const;
	float GetMaxAngularSpeed() const;
	bool IsKeyPressed(const uint8_t* keyState);
	void SetMaxForwardSpeed(float speed);
	void SetMaxAngularSpeed(float speed);
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	int mForwardKey, mBackwardKey;
	int mClockwiseKey, mCounterClockwiseKey;
};

