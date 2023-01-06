#pragma once

#include"include/ControlState.h"
#include"include/CustomMath.h"

class GameObject;
class ControllerState;

class ControllerControlState : public ControlState
{
public:
	ControllerControlState();
	~ControllerControlState() = default;

	virtual void OnEnter(InputComponent * owner) override;
	virtual void OnUpdate(InputComponent* owner, float deltaTime) override;
	virtual void OnProcessInput(InputComponent* owner, const InputState& state) override;
	virtual void OnExit(InputComponent * owner) override; 
	virtual ButtonState GetMappedState(InputComponent* owner, const std::string& actionName) override;
	virtual bool GetMappedValue(InputComponent* owner, const std::string& actionName) override;
	virtual State GetEnumState() const override;
	virtual bool IsMoving() const override;
private:
	Vector3 GetControllerMoveDirection(ControllerState* controller, GameObject* owner) const;
private:
	Vector3 mVelocity;
	float mSpeed;
};

