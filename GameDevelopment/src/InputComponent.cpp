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
	mStates.insert({ ControlState::State::EKeyboard, std::make_shared<KeyboardControlState>() });
	mStates.insert({ ControlState::State::EController, std::make_shared<ControllerControlState>() });
	this->ChangeState(ControlState::State::EKeyboard);

	mOwner->GetGame()->GetInputSystem()->AddInputObserver(this);
}

InputComponent::~InputComponent()
{
	mOwner->GetGame()->GetInputSystem()->RemoveInputObserver(this);
}

void InputComponent::Update(float deltaTime)
{
	mCurrentState->OnUpdate(this, deltaTime);
}

void InputComponent::ProcessInput(const InputState& inputState)
{
	mCurrentState->OnProcessInput(this, inputState);
}

bool InputComponent::IsMoving() const
{
	return mCurrentState->IsMoving();
}

void InputComponent::ChangeState(ControlState::State state)
{
	if (mCurrentState) {
		mCurrentState->OnExit(this);
	}

	mCurrentState = mStates.at(state);
	mCurrentState->OnEnter(this);
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
			mController = nullptr;
			mController->SetIsUsed(false);
			this->ChangeState(ControlState::State::EKeyboard);
		}
		break;
	default:
		break;
	}
}
