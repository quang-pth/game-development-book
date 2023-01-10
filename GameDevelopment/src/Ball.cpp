#include "include/Ball.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/TransformComponent.h"
#include "include/BallMoveComponent.h"
#include "include/MoveComponent.h"
#include "include/MeshComponent.h"
#include "include/BoxComponent.h"
#include "include/Mesh.h"

const float MAX_DISTANCE = 3000.0f;
const float MAX_FORWARD_SPEED = 300.0f;

Ball::Ball(Game* game, const std::string& name) : 
	GameObject(game, name), mDistance(MAX_DISTANCE)
{
	GameObject::GetTransform()->SetScale(3.0f);

	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(game->GetRenderer()->GetMesh("Assets/Chapter9/Sphere.gpmesh"));

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
}

void Ball::Deactivate()
{
	GameObject::Deactivate();
	mDistance = MAX_DISTANCE;
}
