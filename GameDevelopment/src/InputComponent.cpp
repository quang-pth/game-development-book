#include "include/InputComponent.h"
#include "include/GameObject.h"
#include "include/Game.h"
#include "include/CustomMath.h"
#include "include/ControllerState.h"
#include "include/TransformComponent.h"
#include "include/ControllerControlState.h"
#include "include/KeyboardControlState.h"
#include<SDL2/SDL.h>
#include <iostream>

InputComponent::InputComponent(GameObject* owner, int updateOrder) : 
	MoveComponent(owner, updateOrder), mController(nullptr)
{
	mControlStates.insert({ ControlState::State::EKeyboard, std::make_shared<KeyboardControlState>() });
	mControlStates.insert({ ControlState::State::EController, std::make_shared<ControllerControlState>() });
	this->ChangeState(ControlState::State::EKeyboard);

	mOwner->GetGame()->GetInputSystem()->AddInputObserver(this);
}

InputComponent::~InputComponent()
{
	mOwner->GetGame()->GetInputSystem()->RemoveInputObserver(this);
}

void InputComponent::Update(float deltaTime)
{
	if (mCurrentControlState) {
		mCurrentControlState->OnUpdate(this, deltaTime);
	}
}

void InputComponent::ProcessInput(const InputState& inputState)
{
	if (mCurrentControlState) {
		mCurrentControlState->OnProcessInput(this, inputState);
	}
}

bool InputComponent::IsMoving() const
{
	if (mCurrentControlState->GetEnumState() == ControlState::State::EController) {
		return mVelocity != Vector3::Zero;
	}
	
	// Controlled by Keyboard
	return mForwardSpeed != 0.0f;
}

void InputComponent::ChangeState(ControlState::State state)
{
	if (mCurrentControlState) {
		mCurrentControlState->OnExit(this);
	}

	mCurrentControlState = mControlStates.at(state);
	mCurrentControlState->OnEnter(this);
}

void InputComponent::OnControllerInputHandler(ControllerState* controller, InputObserver::Event inputEvent)
{
	switch (inputEvent)
	{
	case InputObserver::Event::EAdded:
		if (mController == nullptr && !controller->GetIsUsed()) {
			mController = controller;
			mController->SetIsUsed(true);
			this->ChangeState(ControlState::State::EController);
		}
		break;
	case InputObserver::Event::ERemoved:
		if (mController != nullptr && controller->GetInstanceID() == mController->GetInstanceID()) {
			mController->SetIsUsed(false);
			mController = nullptr;
			this->ChangeState(ControlState::State::EKeyboard);
		}
		break;
	default:
		break;
	}
}

Vector3 InputComponent::GetMoveDirectionFromController() const
{
	const Vector2& value = mController->GetLeftStick();
	return Vector3::Transform(Vector3(value.y, value.x), mOwner->GetTransform()->GetRotation());
}
