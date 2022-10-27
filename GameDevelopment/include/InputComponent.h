#pragma once

#include "include/MoveComponent.h"
#include "include/Enums.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(class GameObject* owner, int updateOrder = 4);
	~InputComponent();
	void Update(float deltaTime) override;
	void ProcessInput(const uint8_t* keyState) override;
	float GetMaxForwardSpeed() const;
	void SetMaxForwardSpeed(float speed);
	int GetForwardLeftKey() const;
	int GetForwardRightKey() const;
	void SetState(EMovement state);
	EMovement GetState() const;
	bool RightKeyIsClicked();
private:
	float mMaxForwardSpeed;
	bool mRightKeyIsClicked;
	int mForwardLeftKey, mForwardRightKey;
	EMovement mState;
};

