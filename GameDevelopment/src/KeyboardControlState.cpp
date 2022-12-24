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
	FPSGameObject* fpsGameObject = static_cast<FPSGameObject*>(owner->mOwner);
	float forwardSpeed = 0.0f;
	if (inputSystem->GetMappedKeyValue("MoveForward")) {
		forwardSpeed += fpsGameObject->GetForwardSpeed();
	}
	if (inputSystem->GetMappedKeyValue("MoveBackward")) {
		forwardSpeed -= fpsGameObject->GetForwardSpeed();
	}
	owner->SetForwardSpeed(forwardSpeed);
	float strafeSpeed = 0.0f;
	if (inputSystem->GetMappedKeyValue("MoveRight")) {
		strafeSpeed += fpsGameObject->GetStrafeSpeed();
	}
	if (inputSystem->GetMappedKeyValue("MoveLeft")) {
		strafeSpeed -= fpsGameObject->GetStrafeSpeed();
	}
	owner->SetStrafeSpeed(strafeSpeed);
	// ================== MOUSE =======================
	const Vector2& mouseRelativePos = inputSystem->GetMouseRelativePosition();
	const float maxAngularSpeed = Math::Pi * 0.1f; // Max rotation speed per second
	// Rotate horizontally
	float angularSpeed = mouseRelativePos.x * maxAngularSpeed;
	owner->SetAngularSpeed(angularSpeed);
	// Rotate vertically
	angularSpeed = mouseRelativePos.y * maxAngularSpeed;
	owner->mOwner->GetGame()->GetFPSGameObject()->GetFPSCamera()->SetPitchSpeed(angularSpeed);
}

void KeyboardControlState::OnExit(InputComponent* owner)
{
	owner->SetForwardSpeed(static_cast<FPSGameObject*>(owner->mOwner)->GetForwardSpeed());
	owner->SetStrafeSpeed(static_cast<FPSGameObject*>(owner->mOwner)->GetStrafeSpeed());
}

ControlState::State KeyboardControlState::GetEnumState() const
{
	return ControlState::State::EKeyboard;
}
