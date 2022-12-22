#include "KeyboardControlState.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/Game.h"
#include "include/GameObject.h"
#include "include/FPSGameObject.h"
#include "include/FPSCameraComponent.h"
#include "include/InputSystem.h"
#include "include/CustomMath.h"
#include <iostream>

void KeyboardControlState::OnEnter(InputComponent* owner)
{
	owner->SetForwardSpeed(0.0f);
	owner->SetStrafeSpeed(0.0f);
}

void KeyboardControlState::OnUpdate(InputComponent* owner, float deltaTime)
{
	TransformComponent* transformComponent = owner->mOwner->GetTransform();
	
	if (!Math::NearZero(owner->mForwardSpeed) || !Math::NearZero(owner->mStrafeSpeed)) {
		Vector3 position = transformComponent->GetPosition();
		position += owner->mOwner->GetForward() * owner->mForwardSpeed * deltaTime;
		position += owner->mOwner->GetRight() * owner->mStrafeSpeed * deltaTime;
		transformComponent->SetPosition(position);
	}

	if (!Math::NearZero(owner->mAngularSpeed)) {
		float angle = owner->mAngularSpeed * deltaTime;
		Quaternion inc(Vector3::UnitZ, angle);
		transformComponent->SetRotation(
			Quaternion::Concatenate(transformComponent->GetRotation(), inc)
		);
	}
}

void KeyboardControlState::OnProcessInput(InputComponent* owner, const InputState& state)
{
	InputSystem* inputSystem = owner->mOwner->GetGame()->GetInputSystem();
	float forwardSpeed = 0.0f;
	if (inputSystem->GetMappedKeyValue("MoveForward", &state.KeyBoard)) {
		forwardSpeed += owner->mForwardSpeed;
	}
	if (inputSystem->GetMappedKeyValue("MoveBackward", &state.KeyBoard)) {
		forwardSpeed -= owner->mForwardSpeed;
	}
	owner->SetForwardSpeed(forwardSpeed);
	float strafeSpeed = 0.0f;
	if (inputSystem->GetMappedKeyValue("MoveRight", &state.KeyBoard)) {
		strafeSpeed += owner->mStrafeSpeed;
	}
	if (inputSystem->GetMappedKeyValue("MoveLeft", &state.KeyBoard)) {
		strafeSpeed -= owner->mStrafeSpeed;
	}
	owner->SetStrafeSpeed(strafeSpeed);
	// MOUSE
	const Vector2& mouseRelativePos = inputSystem->GetMouseRelativePosition();
	float maxMouseSpeed = 500.0f; // Max mouse speed per frame
	const float maxAngularSpeed = Math::Pi * 8; // Max rotation speed per second
	float angularSpeed = 0.0f;
	angularSpeed = mouseRelativePos.x / maxMouseSpeed;
	angularSpeed *= maxAngularSpeed;
	owner->SetAngularSpeed(angularSpeed);
	owner->mOwner->GetGame()->GetFPSGameObject()->GetFPSCamera()->SetPitchSpeed(-mouseRelativePos.y);
}

void KeyboardControlState::OnExit(InputComponent* owner)
{
}

ControlState::State KeyboardControlState::GetEnumState() const
{
	return ControlState::State::EKeyboard;
}
