#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "CustomMath.h"
#include <iostream>

MoveComponent::MoveComponent(GameObject* owner, int updateOrder, std::string name) : 
	Component(owner, updateOrder, name), 
	mForwardSpeed(30.0f), mDirection(Direction::Right),
	mMass(1.0f), mSumOfForces(0.0f, 0.0f), mForceVelocity(0.0f, 0.0f), 
	mForceMode(ForceMode::Impulse)
{
}

void MoveComponent::Update(float deltaTime)
{
	// Velocity of forces that applied on the gameobject
	Vector2 acceleration = mSumOfForces * (1 / mMass);
	mForceVelocity += acceleration * deltaTime;
	if (mForceMode == ForceMode::Impulse) {
		mSumOfForces = Vector2::Zero;
	}

	Vector2 position = mOwner->pTransform->GetPosition();
	Vector2 velocity = mForceVelocity + mOwner->GetForward() * mForwardSpeed;
	position += velocity * deltaTime;
	mOwner->pTransform->SetPosition(position);
}

float MoveComponent::GetForwardSpeed() const
{
	return mForwardSpeed;
}

Vector2 MoveComponent::GetVelocity()
{
	return mForceVelocity + mOwner->GetForward() * mForwardSpeed;
}

void MoveComponent::SetForwardSpeed(float speed)
{
	mForwardSpeed = speed;
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

void MoveComponent::ToggleHorizontalDirection(float speed)
{
	if (mDirection == Direction::Right) {
		mDirection = Direction::Left;
		this->SetForwardSpeed(speed * (-1.0f));
	}
	else {
		mDirection = Direction::Right;
		this->SetForwardSpeed(speed);
	}
}

Direction MoveComponent::GetDirection() const
{
	return mDirection;
}

void MoveComponent::SetDirection(Direction direction)
{
	mDirection = direction;
}
