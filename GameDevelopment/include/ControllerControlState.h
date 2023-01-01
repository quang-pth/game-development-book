#pragma once

#include"include/ControlState.h"

class ControllerControlState : public ControlState
{
public:
	ControllerControlState();
	~ControllerControlState() = default;

	virtual void OnEnter(InputComponent * owner) override;
	virtual void OnUpdate(InputComponent* owner, float deltaTime) override;
	virtual void OnProcessInput(InputComponent* owner, const InputState& state) override;
	virtual void OnExit(InputComponent * owner) override;
	virtual State GetEnumState() const override;
private:
	float mSpeed;
};

