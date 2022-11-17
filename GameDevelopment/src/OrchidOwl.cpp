#include "OrchidOwl.h"

#include "include/Game.h"
#include "include/Animation.h"
#include "include/TransformComponent.h"
#include "include/AnimatorComponent.h"
#include "include/CircleComponent.h"
#include "include/MoveComponent.h"
#include "include/AIComponent.h"
// AI
#include "include/AIState.h"
#include "include/AIPatrol.h"
#include "include/AIAttack.h"
#include "include/AIDeath.h"

#include "include/Weapon.h"

OrchidOwl::OrchidOwl(Game* game, const std::string& name) :
	Enemy(game, name),
	mPatrolDuration(1.5f), mCurrentPatrolTime(0.0f)
{
	mWeapon->SetAttackInterval(.5f);

	mForwardSpeed = 30.0f;
	mMoveComponent->SetForwardSpeed(mForwardSpeed);
	
	pTransform->SetPosition(Vector2(600.0f, 50.0f));
	pTransform->SetScale(1.5f);

	/*
	* ANIMATIONS
	*/
	// Walking
	std::vector<SDL_Texture*> runningTextures = {
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Running/tile000.png"),
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Running/tile001.png"),
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Running/tile002.png"),
	};
	std::shared_ptr<Animation> runningAnimation = std::make_shared<Animation>("Running", runningTextures);
	runningAnimation->SetFPS(10.0f);
	// Idle
	std::vector<SDL_Texture*> idleTextures = {
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Idle/tile000.png"),
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Idle/tile001.png"),
	};
	std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>("Idle", idleTextures);
	idleAnimation->SetFPS(1.5f);
	// Jump
	std::vector<SDL_Texture*> hurtTextures = {
		game->GetTexture("Assets/Shooter/Enemy/OrchidOwl/Hurt/tile000.png"),
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
	mAI->ChangeState("AIPatrol");
}

OrchidOwl::~OrchidOwl()
{
}

void OrchidOwl::UpdateGameObject(float deltaTime)
{
	mWeapon->Update(deltaTime);
}

void OrchidOwl::ActAsState(float deltaTime)
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

void OrchidOwl::Patrol(float deltaTime)
{
	mCurrentPatrolTime -= deltaTime;
	mMoveComponent->Update(deltaTime);

	if (mCurrentPatrolTime < 0.0f) {
		mMoveComponent->ToggleHorizontalDirection(mForwardSpeed);
		mAnimator->FlipTexture(mMoveComponent->GetDirection() == Direction::Left);
		mCurrentPatrolTime = mPatrolDuration;
	}
}

void OrchidOwl::Attack(float deltaTime)
{
 	mWeapon->Fire();
}

void OrchidOwl::Death(float deltaTime)
{
}
