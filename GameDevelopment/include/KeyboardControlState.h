#pragma once

#include "include/ControlState.h"

class KeyboardControlState : public ControlState
{
public:
	KeyboardControlState();
	~KeyboardControlState() = default;

	virtual void OnEnter(InputComponent* owner) override;
	virtual void OnUpdate(InputComponent* owner, float deltaTime) override;
	virtual void OnProcessInput(InputComponent* owner, const InputState& state) override;
	virtual void OnExit(InputComponent* owner) override;
	virtual State GetEnumState() const override;
	virtual bool IsMoving() const override;
private:
	float mForwardSpeed, mStrafeSpeed;
};

