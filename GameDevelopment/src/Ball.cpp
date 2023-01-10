#include "include/Ball.h"
#include "include/Game.h"
#include "include/FPSGameObject.h"
#include "include/Renderer.h"
#include "include/TransformComponent.h"
#include "include/BallMoveComponent.h"
#include "include/MoveComponent.h"
#include "include/MeshComponent.h"
#include "include/BoxComponent.h"
#include "include/Mesh.h"
#include <iostream>

const float MAX_DISTANCE = 2000.0f;
const float MAX_FORWARD_SPEED = 500.0f;

Ball::Ball(Game* game, const std::string& name) : 
	GameObject(game, name), mDistance(MAX_DISTANCE)
{
	GameObject::GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	GameObject::GetTransform()->SetScale(0.5f);

	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter6/Sphere.gpmesh"));

	mBoxComponent = new BoxComponent(this);
	mBoxComponent->SetObjectBox(mMeshComponent->GetMesh()->GetBox());

	mBallMoveComponent = new BallMoveComponent(this);
	mBallMoveComponent->SetForwardSpeed(MAX_FORWARD_SPEED);

	this->Deactivate();
}

void Ball::UpdateGameObject(float deltaTime)
{
	GameObject::UpdateGameObject(deltaTime);

	mDistance -= mBallMoveComponent->GetForwardSpeed() * deltaTime;
	if (mDistance < 0.0f) {
		this->Deactivate();
	}
}

void Ball::Activate()
{
	GameObject::Activate();
	mMeshComponent->SetVisible(true);
	mDistance = MAX_DISTANCE;
}

void Ball::Deactivate()
{
	GameObject::Deactivate();
	mMeshComponent->SetVisible(false);
	mBallMoveComponent->SetForwardVelocity(Vector3::Zero);
	mBallMoveComponent->SetStrafeVelocity(Vector3::Zero);
}

void Ball::Fire(const Vector3& startPos, const Vector3& fireDirection)
{
	GameObject::GetTransform()->SetPosition(startPos);
	mBallMoveComponent->SetForwardVelocity(fireDirection);
	mBallMoveComponent->SetStrafeVelocity(Vector3::Zero);
	this->Activate();
}