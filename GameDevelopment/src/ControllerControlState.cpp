#include "include/ControllerControlState.h"
#include "include/InputComponent.h"
#include "include/TransformComponent.h"
#include "include/InputSystem.h"
#include "include/GameObject.h"
#include "include/FPSGameObject.h"
#include "include/Game.h"
#include "include/FPSCameraComponent.h"
#include <iostream>

void ControllerControlState::OnEnter(InputComponent* owner)
{
	owner->SetForwardSpeed(200.0f);
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
		owner->SetVelocity(owner->GetMoveDirectionFromController());

		const Vector2& rotation = controller->GetRightStick();
		const float maxAngularSpeed = Math::Pi * 1.5; 
		owner->SetAngularSpeed(rotation.x * maxAngularSpeed);
		owner->mOwner->GetGame()->GetFPSGameObject()->GetFPSCamera()->SetPitchSpeed(-rotation.y);
	}
}

void ControllerControlState::OnExit(InputComponent* owner)
{
	owner->SetForwardSpeed(0.0f);
}

ControlState::State ControllerControlState::GetEnumState() const
{
	return ControlState::State::EController;
}