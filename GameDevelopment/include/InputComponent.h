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
	void SetMaxForwardSpeed(float speed);
	int GetForwardLeftKey() const;
	int GetForwardRightKey() const;
private:
	float mMaxForwardSpeed;
	int mForwardLeftKey, mForwardRightKey;
};

