#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "CustomMath.h"

MoveComponent::MoveComponent() : Component(), mForwardSpeed(0.0f), mAngularSpeed(0.0f)
{
}

MoveComponent::MoveComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder), mForwardSpeed(0.0f), mAngularSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
{
	TransformComponent* transformComponent = mOwner->GetTransform();
	
	if (!Math::NearZero(mForwardSpeed)) {
		Vector2 position = transformComponent->GetPosition();
		position += mOwner->GetForward() * mForwardSpeed * deltaTime;
		transformComponent->SetPosition(position);
	}

	if (!Math::NearZero(mAngularSpeed)) {
		float rotation = transformComponent->GetRotation();
		rotation += mAngularSpeed * deltaTime;
		transformComponent->SetRotation(rotation);
	}
}
