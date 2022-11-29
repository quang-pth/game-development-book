#include "include/Laser.h"
#include "include/Game.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/CircleComponent.h"
#include "include/TransformComponent.h"
#include "include/TileMap.h"
#include "include/Asteroid.h"
#include "include/Health.h"
#include "include/Enemy.h"
#include "include/Mario.h"
#include "include/Tile.h"
#include <iostream>

Laser::Laser(Game* game, bool enemyLaser, const std::string& name) :
	GameObject(game, name),
	mLifeTime(1.5f),
	mCurrentLifeTime(1.5f),
	mForwardSpeed(270.0f),
	mDamage(5.0f), mIsEnemyLaser(enemyLaser)
{
	mMoveComponent = new MoveComponent(this);
	mMoveComponent->SetForwardSpeed(mForwardSpeed);

	mSpriteComponent = new SpriteComponent(this);
	mSpriteComponent->SetTexture(GameObject::GetGame()->GetTexture("Assets/Shooter/Hero/Bullet/tile000.png"));

	mCircleComponent = new CircleComponent(this);
	mCircleComponent->SetRadius(4.0f);
}

void Laser::UpdateGameObject(float deltaTime)
{
	mCurrentLifeTime -= deltaTime;
	this->CheckCollisions();
	mMoveComponent->Update(deltaTime);
}

void Laser::SetDirection(int direction)
{
	mMoveComponent->SetForwardSpeed(direction * mForwardSpeed);
}

void Laser::SetTexture(const std::string& filePath)
{
	mSpriteComponent->SetTexture(GameObject::GetGame()->GetTexture(filePath));
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
		this->ResetLaser();
	}
}

void Laser::ResetLaser()
{
	GameObject::SetState(State::EDeactive);
	mMoveComponent->SetForwardSpeed(mForwardSpeed);
	mCurrentLifeTime = mLifeTime;
}

void Laser::CheckCollisions()
{
	if (!mIsEnemyLaser) {
		for (Enemy* enemy : mGame->GetEnemies()) {
			if (CircleComponent::IsIntersect(enemy->GetCircleComponent(), mCircleComponent)) {
				if (!enemy->IsActive()) continue;
				
				enemy->ReceiveDamage(mDamage);
				this->ResetLaser();
			}
		}
	}
	else {
		if (!mGame->GetHero()->IsActive()) return;
		
		if (CircleComponent::IsIntersect(mGame->GetHero()->circleComponent, mCircleComponent)) {
			mGame->GetHero()->ReceiveDamage(mDamage);
			this->ResetLaser();
		}
	}
}
