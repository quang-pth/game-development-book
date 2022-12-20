#include "include/InputComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/CustomMath.h"
#include "include/ControllerState.h"
#include "include/TransformComponent.h"
#include<SDL2/SDL.h>
#include <iostream>

InputComponent::InputComponent(GameObject* owner, int updateOrder) : 
	MoveComponent(owner, updateOrder), mController(),
	mMaxForwardSpeed(500.0f), mMaxAngularSpeed(Math::Pi),
	mControllerIdx(0)
{
	mOwner->GetGame()->GetInputSystem()->AddInputObserver(this);
}

InputComponent::~InputComponent()
{
	mOwner->GetGame()->GetInputSystem()->RemoveInputObserver(this);
}

void InputComponent::ProcessInput(const InputState& inputState)
{
	if (mController != nullptr && mController->GetIsConnected())
	{
		const Vector2& direction = mController->GetLeftStick();
		const Vector3& velocity = Vector3::Transform(Vector3(direction.y, direction.x), mOwner->GetTransform()->GetRotation());
		MoveComponent::SetVelocity(velocity);
		
		float angularSpeed = 0.0f;
		if (mController->GetLeftTrigger()) {
			angularSpeed -= mMaxAngularSpeed;
		}
		if (mController->GetRightTrigger()) {
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

void InputComponent::OnNotify(ControllerState* controller, InputObserver::Event inputEvent)
{
	switch (inputEvent)
	{
	case InputObserver::Event::EAdded:
		if (mController == nullptr) {
			mController = controller;
			mController->SetIsUsed(true);
		}
		break;
	case InputObserver::Event::ERemoved:
		if (mController != nullptr && controller->GetInstanceID() == mController->GetInstanceID()) {
			mController->SetIsUsed(false);
			mController = nullptr;
		}
		break;
	default:
		break;
	}
}
