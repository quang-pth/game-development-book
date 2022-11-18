#include "Enemy.h"
#include "include/Game.h"
#include "include/TransformComponent.h"
#include "include/AnimatorComponent.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/CircleComponent.h"
#include "include/AIComponent.h"
#include "include/RigidBodyComponent.h"
#include "include/AIState.h"
#include "include/Health.h"
#include "include/Weapon.h"
#include "include/Unit.h"

Enemy::Enemy(Game* game, const std::string& name) :
	GameObject(game, name),
	mForwardSpeed(200.0f), 
	mAttackRadius(250.0f), mIsAttacked(false)
{
	mHealth.reset(new Health(20.0f));
	mWeapon.reset(new Weapon(this, true));

	mAnimator = new AnimatorComponent(this);
	
	mMoveComponent = new MoveComponent(this);

	mCircleComponent = new CircleComponent(this);
	
	mAI = new AIComponent(this);

	mRigidBodyComponent = new RigidBodyComponent(this);
}

Enemy::~Enemy()
{

}

void Enemy::UpdateGameObject(float deltaTime)
{
	const Vector2& position = Unit::MetersToPixels(mRigidBodyComponent->GetBody()->GetPosition());
	pTransform->SetPosition(position);
}

void Enemy::ActAsState(float deltaTime)
{
	if (mAI->GetState()->GetName() == "AIPatrol")
	{
		this->Patrol(deltaTime);
	}
	else if (mAI->GetState()->GetName() == "AIAttack") {
		this->Attack(deltaTime);
	}
	else if (mAI->GetState()->GetName() == "AIDeath") {
		this->Death(deltaTime);
	}
}

CircleComponent* Enemy::GetCircleComponent() const
{
	return mCircleComponent;
}

MoveComponent* Enemy::GetMoveComponent() const
{
	return mMoveComponent;
}

AIComponent* Enemy::GetAIComponent() const
{
	return mAI;
}

AnimatorComponent* Enemy::GetAnimatorComponent() const
{
	return mAnimator;
}

RigidBodyComponent* Enemy::GetRigidBodyComponent() const
{
	return mRigidBodyComponent;
}

float Enemy::GetAttackRadius() const
{
	return mAttackRadius;
}

bool Enemy::IsAttacked() const
{
	return mIsAttacked;
}

void Enemy::SetIsAttacked(bool isAtacked)
{
	mIsAttacked = isAtacked;
}

void Enemy::ReceiveDamage(float amount)
{
	mIsAttacked = true;
	mHealth->ReceiveDamage(amount);
}

bool Enemy::IsDead() const
{
	return mHealth->IsDead();
}

bool Enemy::IsSawPlayer()
{
	const Vector2& distanceVector = (mGame->GetHero()->pTransform->GetPosition() - 
		pTransform->GetPosition()).Normalize();
	return Vector2::Dot(mMoveComponent->GetVelocity(), distanceVector) > 0.0f;
}

bool Enemy::IsNearPlayer()
{
	const Vector2& distanceVector = mGame->GetHero()->pTransform->GetPosition() - pTransform->GetPosition();
	return std::abs(distanceVector.x) < mAttackRadius &&
		std::abs(distanceVector.y) < 5.0f;
}

void Enemy::Patrol(float deltaTime)
{

}

void Enemy::Attack(float deltaTime)
{
	mWeapon->Update(deltaTime);
	mWeapon->Fire();
}

void Enemy::Death(float deltaTime)
{
}
