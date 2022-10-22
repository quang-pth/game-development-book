#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "CustomMath.h"
#include <iostream>

MoveComponent::MoveComponent() : 
	Component(), 
	mForwardSpeed(0.0f), mAngularSpeed(0.0f),
	mMass(1.0f), mForceVelocity(0.0f, 0.0f), mSumOfForces(0.0f, 0.0f),
	mForceMode(ForceMode::Impulse)
{
}

MoveComponent::MoveComponent(GameObject* owner, int updateOrder, std::string name) : 
	Component(owner, updateOrder, name), 
	mForwardSpeed(0.0f), mAngularSpeed(0.0f),
	mMass(1.0f), mSumOfForces(0.0f, 0.0f), mForceVelocity(0.0f, 0.0f), 
	mForceMode(ForceMode::Impulse)
{
}

void MoveComponent::Update(float deltaTime)
{
	TransformComponent* transformComponent = mOwner->GetTransform();

	Vector2 acceleration = mSumOfForces * (1 / mMass);
	mForceVelocity += acceleration * deltaTime;
	if (mForceMode == ForceMode::Impulse) {
		mSumOfForces = Vector2::Zero;
	}
	Vector2 position = transformComponent->GetPosition();
	position += mForceVelocity * deltaTime;
	transformComponent->SetPosition(position);

	if (!Math::NearZero(mAngularSpeed)) {
		float rotation = transformComponent->GetRotation();
		rotation += mAngularSpeed * deltaTime;
		transformComponent->SetRotation(rotation);
	}
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
	mSumOfForces = mOwner->GetForward() * mForwardSpeed;
}

void MoveComponent::SetAngularSpeed(float speed)
{
	mAngularSpeed = speed;
}

void MoveComponent::AddForce(const Vector2& force, ForceMode forceMode)
{
	mSumOfForces += force;
	mForceMode = forceMode;
}

void MoveComponent::ResetForce()
{
	mForceVelocity = Vector2::Zero;
	mSumOfForces = Vector2::Zero;
}
