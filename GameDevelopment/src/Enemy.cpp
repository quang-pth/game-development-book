#include "Enemy.h"
#include "include/Game.h"
#include "include/AnimatorComponent.h"
#include "include/MoveComponent.h"
#include "include/SpriteComponent.h"
#include "include/CircleComponent.h"

Enemy::Enemy(Game* game, const std::string& name) :
	GameObject(game, name), mAI(), mStates(), mCurrentState()
{
	mAnimator = new AnimatorComponent(this);
	mMoveComponent = new MoveComponent(this);
	mSpriteComponent = new SpriteComponent(this);
	mCircleComponent = new CircleComponent(this);
}

Enemy::~Enemy()
{
	while (!mStates.empty()) {
		delete mStates.back();
	}
}

void Enemy::UpdateGameObject(float deltaTime)
{
}

void Enemy::Cooldown(float deltaTime)
{
}

CircleComponent* Enemy::GetCircleComponent() const
{
	return mCircleComponent;
}
