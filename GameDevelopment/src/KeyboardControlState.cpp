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

KeyboardControlState::KeyboardControlState() : mForwardSpeed(200.0f), mStrafeSpeed(100.0f)
{
}

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

	static float maxYawAngle = Math::Pi;
	float angle = owner->mAngularSpeed * deltaTime;
	angle = Math::Clamp(angle, -maxYawAngle, maxYawAngle);
		
	if (!Math::NearZero(angle)) {
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
	if (inputSystem->GetMappedKeyValue("MoveForward")) {
		forwardSpeed += mForwardSpeed;
	}
	if (inputSystem->GetMappedKeyValue("MoveBackward")) {
		forwardSpeed -= mForwardSpeed;
	}
	owner->SetForwardSpeed(forwardSpeed);
	float strafeSpeed = 0.0f;
	if (inputSystem->GetMappedKeyValue("MoveRight")) {
		strafeSpeed += mStrafeSpeed;
	}
	if (inputSystem->GetMappedKeyValue("MoveLeft")) {
		strafeSpeed -= mStrafeSpeed;
	}
	owner->SetStrafeSpeed(strafeSpeed);
	// ================== MOUSE =======================
	const Vector2& mouseRelativePos = inputSystem->GetRelativeMouse().Position;
	const float maxYawSpeed = Math::Pi * 0.08f; // Max rotation speed per second
	// Rotate horizontally
	float angularSpeed = mouseRelativePos.x * maxYawSpeed;
	owner->SetAngularSpeed(angularSpeed);
	// Rotate vertically
	const float maxPitchSpeed = Math::Pi * 0.06f; // Max rotation speed per second
	angularSpeed = mouseRelativePos.y * maxPitchSpeed;
	owner->mOwner->GetGame()->GetFPSGameObject()->GetFPSCamera()->SetPitchSpeed(angularSpeed);
}

void KeyboardControlState::OnExit(InputComponent* owner)
{
	owner->SetForwardSpeed(mForwardSpeed);
	owner->SetStrafeSpeed(mStrafeSpeed);
}

ControlState::State KeyboardControlState::GetEnumState() const
{
	return ControlState::State::EKeyboard;
}
