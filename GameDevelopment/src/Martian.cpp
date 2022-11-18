#include "Martian.h"
#include "include/Game.h"
// COMPONENTS
#include "include/TransformComponent.h"
#include "include/AnimatorComponent.h"
#include "include/RigidBodyComponent.h"
#include "include/CircleComponent.h"
#include "include/AIComponent.h"
// STATE
#include "include/AIPatrol.h"
#include "include/AIDeath.h"
#include "include/AIAttack.h"
#include "include/AIInjured.h"
// OTHER
#include "include/Unit.h"
#include "include/Weapon.h"
#include "include/Animation.h"
#include <iostream>

Martian::Martian(Game* game, const std::string& name) : 
	Enemy(game, name), 
	mPatrolDuration(2.5f), mCurrentPatrolTime(2.5f)
{
	mAttackRadius = 100.0f;
	mWeapon->SetAttackInterval(.5f);

	mForwardSpeed = 100.0f;
	mMoveComponent->SetForwardSpeed(mForwardSpeed);

	pTransform->SetPosition(Vector2(600.0f, 500.0f));
	pTransform->SetScale(1.5f);

	mCircleComponent->SetRadius(4.0f);

	/*
	* ANIMATIONS
	*/
	// Walking
	std::vector<SDL_Texture*> runningTextures = {
		game->GetTexture("Assets/Shooter/Enemy/Martian/Running/tile000.png"),
		game->GetTexture("Assets/Shooter/Enemy/Martian/Running/tile001.png"),
		game->GetTexture("Assets/Shooter/Enemy/Martian/Running/tile002.png"),
		game->GetTexture("Assets/Shooter/Enemy/Martian/Running/tile003.png"),
	};
	std::shared_ptr<Animation> runningAnimation = std::make_shared<Animation>("Running", runningTextures);
	runningAnimation->SetFPS(10.0f);
	// Idle
	std::vector<SDL_Texture*> idleTextures = {
		game->GetTexture("Assets/Shooter/Enemy/Martian/Idle/tile000.png"),
		game->GetTexture("Assets/Shooter/Enemy/Martian/Idle/tile001.png"),
	};
	std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>("Idle", idleTextures);
	idleAnimation->SetFPS(1.5f);
	// Jump
	std::vector<SDL_Texture*> hurtTextures = {
		game->GetTexture("Assets/Shooter/Enemy/Martian/Hurt/tile000.png"),
	};
	std::shared_ptr<Animation> hurtAnimation = std::make_shared<Animation>("Hurt", hurtTextures, false);
	idleAnimation->SetFPS(1.5f);

	// mAnimator
	mAnimator->AddAnimation(runningAnimation);
	mAnimator->AddAnimation(idleAnimation);
	mAnimator->AddAnimation(hurtAnimation);
	mAnimator->SetAnimation(runningAnimation->name);

	mCircleComponent->SetRadius(16.0f * pTransform->GetScale());

	mAI->RegisterState(new AIPatrol(mAI));
	mAI->RegisterState(new AIAttack(mAI));
	mAI->RegisterState(new AIDeath(mAI));
	mAI->RegisterState(new AIInjured(mAI));
	mAI->ChangeState("AIPatrol");

	const Vector2& offsetPos = Vector2(TILE_SIZE, 0.0f) * pTransform->GetScale() * 0.5f;
	mRigidBodyComponent->SetBodyType(EBody::DYNAMIC);
	mRigidBodyComponent->SetPosition(pTransform->GetPosition() + offsetPos);
	mRigidBodyComponent->SetDimension(Vector2(TILE_SIZE, TILE_SIZE) * pTransform->GetScale() * 0.3f);
	mRigidBodyComponent->Init();
}

Martian::~Martian()
{
}

void Martian::Patrol(float deltaTime)
{
	mCurrentPatrolTime -= deltaTime;
	const Vector2& velocity = mMoveComponent->GetVelocity() * deltaTime;
	mRigidBodyComponent->Move(velocity);
	
	if (mCurrentPatrolTime < 0.0f) {
		this->ChangeDirection();
		mCurrentPatrolTime = mPatrolDuration;
	}
}

void Martian::Death(float deltaTime)
{
}

void Martian::ConstraintInBounds()
{
}

void Martian::ChangeDirection()
{
	mMoveComponent->ToggleHorizontalDirection(mForwardSpeed);
	mAnimator->FlipTexture(mMoveComponent->GetDirection() == Direction::Left);
}
