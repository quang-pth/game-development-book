#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "CustomMath.h"
#include <iostream>

MoveComponent::MoveComponent(GameObject* owner, int updateOrder, std::string name) : 
	Component(owner, updateOrder, name), 
	mForwardSpeed(200.0f), mAngularSpeed(0.0f), mStrafeSpeed(100.0f),
	mForwardVelocity(Vector3::Zero), mStrafeVelocity(Vector3::Zero)
{
}

void MoveComponent::Update(float deltaTime)
{
	TransformComponent* transformComponent = mOwner->GetTransform();

	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mStrafeSpeed)) {
		Vector3 position = transformComponent->GetPosition();
		position += mForwardVelocity * mForwardSpeed * deltaTime;
		position += mStrafeVelocity * mStrafeSpeed * deltaTime;
		transformComponent->SetPosition(position);
	}

	static float maxYawAngle = Math::Pi;
	float angle = mAngularSpeed * deltaTime;
	angle = Math::Clamp(angle, -maxYawAngle, maxYawAngle);

	if (!Math::NearZero(angle)) {
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

float MoveComponent::GetStrafeSpeed() const
{
	return mStrafeSpeed;
}

void MoveComponent::SetForwardSpeed(float speed)
{
	mForwardSpeed = speed;
}

void MoveComponent::SetAngularSpeed(float speed)
{
	mAngularSpeed = speed;
}

void MoveComponent::SetStrafeSpeed(float speed)
{
	mStrafeSpeed = speed;
}

void MoveComponent::SetForwardVelocity(const Vector3& velocity)
{
	mForwardVelocity = velocity;
}

void MoveComponent::SetStrafeVelocity(const Vector3& velocity)
{
	mStrafeVelocity = velocity;
}

const Vector3& MoveComponent::GetForwardVelocity() const
{
	return mForwardVelocity;
}

const Vector3& MoveComponent::GetStrafeVelocity() const
{
	return mStrafeVelocity;
}
