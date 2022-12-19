#pragma once

#include<SDL2/SDL.h>
#include "include/MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(class GameObject* owner, int updateOrder = 4);
	~InputComponent();
	void ProcessInput(const InputState& inputState) override;
	float GetMaxForwardSpeed() const;
	float GetMaxAngularSpeed() const;
	void SetMaxForwardSpeed(float speed);
	void SetMaxAngularSpeed(float speed);
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	std::uint16_t mControllerIdx;
};

