#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/TransformComponent.h"
#include "CustomMath.h"
#include <iostream>

MoveComponent::MoveComponent(GameObject* owner, int updateOrder, std::string name) : 
	Component(owner, updateOrder, name), 
	mForwardSpeed(0.0f), mAngularSpeed(0.0f),
	mMass(1.0f), mSumOfForces(Vector3::Zero), mForceVelocity(Vector3::Zero), 
	mForceMode(ForceMode::Impulse)
{
}

void MoveComponent::Update(float deltaTime)
{
	TransformComponent* transformComponent = mOwner->GetTransform();

	// Velocity of forces that applied on the gameobject
	Vector3 acceleration = mSumOfForces * (1 / mMass);
	mForceVelocity += acceleration * deltaTime;
	if (mForceMode == ForceMode::Impulse) {
		mSumOfForces = Vector3::Zero;
	}
	// Move the gameobject by forces
	Vector3 position = transformComponent->GetPosition();

	position += mForceVelocity * deltaTime;
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
	mSumOfForces = mOwner->GetForward() * mForwardSpeed;
}

void MoveComponent::SetAngularSpeed(float speed)
{
	mAngularSpeed = speed;
}

void MoveComponent::AddForce(const Vector3& force, ForceMode forceMode)
{
	mSumOfForces += force;
	mForceMode = forceMode;
}

void MoveComponent::ResetForce()
{
	mForceVelocity = Vector3::Zero;
	mSumOfForces = Vector3::Zero;
}
