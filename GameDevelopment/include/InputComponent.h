#pragma once

#include<SDL2/SDL.h>
#include "include/InputObserver.h"
#include "include/MoveComponent.h"
#include "include/InputSystem.h"

class InputComponent : public MoveComponent, InputObserver
{
public:
	InputComponent(class GameObject* owner, int updateOrder = 4);
	~InputComponent();
	void ProcessInput(const InputState& inputState) override;
	float GetMaxForwardSpeed() const;
	float GetMaxAngularSpeed() const;
	void SetMaxForwardSpeed(float speed);
	void SetMaxAngularSpeed(float speed);
	virtual void OnNotify(ControllerState* controller, InputObserver::Event inputEvent) override;
private:
	ControllerState* mController;
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	std::uint8_t mControllerIdx;
};

