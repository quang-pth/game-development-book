#include "include/Laser.h"
#include "include/Game.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/CircleComponent.h"
#include "include/TransformComponent.h"
#include "include/Asteroid.h"
#include "include/Mario.h"
#include <iostream>

Laser::Laser(Game* game, std::string name) : 
	GameObject(game, name),
	mLifeTime(1.5f),
	mCurrentLifeTime(1.5f),
	mForwardSpeed(150.0f)
{
	mMoveComponent = new MoveComponent(this);
	mMoveComponent->SetForwardSpeed(mForwardSpeed);

	mSpriteComponent = new SpriteComponent(this);
	mSpriteComponent->SetTexture(GameObject::GetGame()->GetTexture("Assets/Shooter/Hero/Bullet/tile000.png"));

	mCircleComponent = new CircleComponent(this);
	mCircleComponent->SetRadius(mSpriteComponent->GetTextureWidth());
}

void Laser::UpdateGameObject(float deltaTime)
{
	mCurrentLifeTime -= deltaTime;
	mMoveComponent->Update(deltaTime);
}

void Laser::SetDirection(int direction)
{
	mMoveComponent->SetForwardSpeed(direction * mForwardSpeed);
}

MoveComponent* Laser::GetMoveComponent() const
{
	return mMoveComponent;
}

SpriteComponent* Laser::GetSpriteComponent() const
{
	return mSpriteComponent;
}

CircleComponent* Laser::GetCircleComponent() const
{
	return mCircleComponent;
}

void Laser::CheckIsAlive()
{
	if (mCurrentLifeTime <= 0) {
		GameObject::SetState(GameObject::State::EDeactive);
		mCurrentLifeTime = mLifeTime;
		mMoveComponent->SetForwardSpeed(mForwardSpeed);
	}
}
