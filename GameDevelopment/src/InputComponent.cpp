#include "include/InputComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/CustomMath.h"
#include "include/InputSystem.h"
#include "include/ControllerState.h"
#include "include/TransformComponent.h"
#include<SDL2/SDL.h>
#include <iostream>

InputComponent::InputComponent(GameObject* owner, int updateOrder) : 
	MoveComponent(owner, updateOrder),
	mMaxForwardSpeed(500.0f), mMaxAngularSpeed(Math::Pi),
	mControllerIdx(0)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::ProcessInput(const InputState& inputState)
{
	const ControllerState& controller = mOwner->GetGame()->GetInputSystem()->GetInputState().Controllers[mControllerIdx];
	if (controller.GetIsConnected()) {
		const Vector2& direction = controller.GetLeftStick();
		const Vector3& velocity = Vector3::Transform(Vector3(direction.y, direction.x), mOwner->GetTransform()->GetRotation());
		MoveComponent::SetVelocity(velocity);
		float angularSpeed = 0.0f;
		if (controller.GetLeftTrigger()) {
			angularSpeed -= mMaxAngularSpeed;
		}
		if (controller.GetRightTrigger()) {
			angularSpeed += mMaxAngularSpeed;
		}
		MoveComponent::SetAngularSpeed(angularSpeed);
	}
}

float InputComponent::GetMaxForwardSpeed() const
{
	return mMaxForwardSpeed;
}

float InputComponent::GetMaxAngularSpeed() const
{
	return mMaxAngularSpeed;
}

void InputComponent::SetMaxForwardSpeed(float speed)
{
	mMaxForwardSpeed = speed;
}

void InputComponent::SetMaxAngularSpeed(float speed)
{
	mMaxAngularSpeed = speed;
}
