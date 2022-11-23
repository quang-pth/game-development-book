#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "CustomMath.h"
#include <iostream>

MoveComponent::MoveComponent(GameObject* owner, int updateOrder, std::string name) : 
	Component(owner, updateOrder, name), 
	mForwardSpeed(30.0f), mDirection(Direction::Right)
{
}

void MoveComponent::Update(float deltaTime)
{
	Vector2 position = mOwner->pTransform->GetPosition();
	position += mOwner->GetForward() * mForwardSpeed * deltaTime;
	mOwner->pTransform->SetPosition(position);
}

float MoveComponent::GetForwardSpeed() const
{
	return mForwardSpeed;
}

Vector2 MoveComponent::GetVelocity()
{
	return mOwner->GetForward() * mForwardSpeed;
}

void MoveComponent::SetForwardSpeed(float speed)
{
	mForwardSpeed = speed;
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
