#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "CustomMath.h"
#include <iostream>

MoveComponent::MoveComponent(GameObject* owner, int updateOrder, std::string name) : 
	Component(owner, updateOrder, name), 
	mForwardSpeed(200.0f), mAngularSpeed(0.0f),
	mVelocity(Vector3::Zero)
{
}

void MoveComponent::Update(float deltaTime)
{
	TransformComponent* transformComponent = mOwner->GetTransform();

	Vector3 position = transformComponent->GetPosition();

	position += mVelocity * mForwardSpeed * deltaTime;
	transformComponent->SetPosition(position);

	if (!Math::NearZero(mAngularSpeed)) {
		float angle = mAngularSpeed * deltaTime;
		Quaternion inc(Vector3::UnitZ, angle);
		transformComponent->SetRotation(
			Quaternion::Concatenate(transformComponent->GetRotation(), inc)
		);
	}
}

void MoveComponent::OnUpdateWorldTransform()
{

}

float MoveComponent::GetForwardSpeed() const
{
	return mForwardSpeed;
}

float MoveComponent::GetAngularSpeed() const
{
	return mAngularSpeed;
}

void MoveComponent::SetForwardSpeed(float speed)
{
	mForwardSpeed = speed;
}

void MoveComponent::SetAngularSpeed(float speed)
{
	mAngularSpeed = speed;
}

void MoveComponent::SetVelocity(const Vector3& velocity)
{
	mVelocity = velocity;
}

const Vector3& MoveComponent::GetVelocity() const
{
	return mVelocity;
}
