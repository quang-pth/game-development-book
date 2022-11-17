#include "Enemy.h"
#include "include/Game.h"
#include "include/AnimatorComponent.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/CircleComponent.h"
#include "include/AIComponent.h"
#include "include/Health.h"
#include "include/Weapon.h"

Enemy::Enemy(Game* game, const std::string& name) :
	GameObject(game, name),
	mAI(),
	mForwardSpeed(200.0f), mAttackRadius(250.0f)
{
	mHealth.reset(new Health(20.0f));
	mWeapon.reset(new Weapon(this, true));

	mAnimator = new AnimatorComponent(this);
	
	mMoveComponent = new MoveComponent(this);

	mCircleComponent = new CircleComponent(this);
	
	mAI = new AIComponent(this);
}

Enemy::~Enemy()
{

}

void Enemy::UpdateGameObject(float deltaTime)
{
}

void Enemy::ActAsState(float deltaTime)
{
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

float Enemy::GetAttackRadius() const
{
	return mAttackRadius;
}

void Enemy::ReceiveDamage(float amount)
{
	mHealth->ReceiveDamage(amount);
}

bool Enemy::IsDead() const
{
	return mHealth->IsDead();
}
