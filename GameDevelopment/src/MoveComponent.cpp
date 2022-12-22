#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "CustomMath.h"
#include <iostream>

MoveComponent::MoveComponent(GameObject* owner, int updateOrder, std::string name) : 
	Component(owner, updateOrder, name), 
	mForwardSpeed(200.0f), mAngularSpeed(0.0f), mStrafeSpeed(100.0f),
	mVelocity(Vector3::Zero)
{
}

void MoveComponent::Update(float deltaTime)
{
	
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

void MoveComponent::SetVelocity(const Vector3& velocity)
{
	mVelocity = velocity;
}

const Vector3& MoveComponent::GetVelocity() const
{
	return mVelocity;
}
