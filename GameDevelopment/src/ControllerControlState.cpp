#include "include/ControllerControlState.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/InputSystem.h"
#include "include/GameObject.h"
#include "include/FPSGameObject.h"
#include "include/Game.h"
#include "include/FPSCameraComponent.h"
#include <iostream>

ControllerControlState::ControllerControlState() : mSpeed(200.0f)
{
}

void ControllerControlState::OnEnter(InputComponent* owner)
{
	owner->SetForwardSpeed(mSpeed);
}

void ControllerControlState::OnUpdate(InputComponent* owner, float deltaTime)
{
	TransformComponent* transformComponent = owner->mOwner->GetTransform();
	Vector3 position = transformComponent->GetPosition();

	position += owner->mVelocity * owner->mForwardSpeed * deltaTime;
	transformComponent->SetPosition(position);

	if (!Math::NearZero(owner->mAngularSpeed)) {
		float angle = owner->mAngularSpeed * deltaTime;
		Quaternion inc(Vector3::UnitZ, angle);
		transformComponent->SetRotation(
			Quaternion::Concatenate(transformComponent->GetRotation(), inc)
		);
	}
}

void ControllerControlState::OnProcessInput(InputComponent* owner, const InputState& state)
{
	ControllerState* controller = owner->mController;
	if (controller != nullptr && controller->GetIsConnected())
	{
		mVelocity = this->GetControllerMoveDirection(controller, owner->mOwner);
		owner->SetVelocity(mVelocity);
		const Vector2& rotation = controller->GetRightStick();
		const float maxAngularSpeed = Math::Pi * 1.5;
		owner->SetAngularSpeed(rotation.x * maxAngularSpeed);
		owner->mOwner->GetGame()->GetFPSGameObject()->GetCamera()->SetPitchSpeed(-rotation.y * maxAngularSpeed);
	}
}

void ControllerControlState::OnExit(InputComponent* owner)
{
	owner->SetForwardSpeed(0.0f);
}

ButtonState ControllerControlState::GetMappedState(InputComponent* owner, const std::string& actionName)
{
	return owner->mOwner->GetGame()->GetInputSystem()->GetMappedButtonState(actionName, owner->mController);
}

bool ControllerControlState::GetMappedValue(InputComponent* owner, const std::string& actionName)
{
	return owner->mOwner->GetGame()->GetInputSystem()->GetMappedButtonValue(actionName, owner->mController);
}

ControlState::State ControllerControlState::GetEnumState() const
{
	return ControlState::State::EController;
}

bool ControllerControlState::IsMoving() const
{
	return mVelocity != Vector3::Zero;
}

Vector3 ControllerControlState::GetControllerMoveDirection(ControllerState* controller, GameObject* owner) const
{
	const Vector2& value = controller->GetLeftStick();
	return Vector3::Transform(Vector3(value.y, value.x), owner->GetTransform()->GetRotation());
}
