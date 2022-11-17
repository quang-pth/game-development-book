#include "Weapon.h"
#include "include/Game.h"
#include "include/GameObject.h"
#include "include/Laser.h"
#include "include/TransformComponent.h"
#include "include/MoveComponent.h"
#include "include/AnimatorComponent.h"

Weapon::Weapon(GameObject* owner, bool isEnemyLaser) :
	mFireInterval(0.5f), mCurrentFireInterval(0.5f),
	mActivateLaserIdx(0), mCapacity(30),
	mFireDirection(Direction::Left), mLasers(), mIsEnemyLaser(isEnemyLaser)
{
	mOwner = owner;
	this->InstantiateLaser();
}

Weapon::~Weapon()
{
}

void Weapon::Update(float deltaTime)
{
	mCurrentFireInterval -= deltaTime;
}

void Weapon::Fire()
{
	if (mCurrentFireInterval > 0.0f) return;

	mActivateLaserIdx++;
	if (mActivateLaserIdx >= mLasers.size()) {
		mActivateLaserIdx = 0;
	}

	MoveComponent* moveComponent = static_cast<MoveComponent*>(mOwner->GetComponent("MoveComponent"));
	AnimatorComponent* animatorComponent = static_cast<AnimatorComponent*>(mOwner->GetComponent("AnimatorComponent"));
	Laser* laser = mLasers[mActivateLaserIdx];

	if (moveComponent->GetDirection() == Direction::Left) {
		Vector2 offset(-5.0f, animatorComponent->GetTextureHeight() / 2 - 3.5f);
		laser->pTransform->SetPosition(mOwner->pTransform->GetPosition() + offset);
		laser->SetDirection(-1);
	}
	else if (moveComponent->GetDirection() == Direction::Right) {
		Vector2 offset(8.0f, animatorComponent->GetTextureHeight() / 2 - 3.5f);
		laser->pTransform->SetPosition(mOwner->pTransform->GetPosition() + offset);
		laser->SetDirection(1);
	}

	laser->SetState(GameObject::State::EActive);
	mCurrentFireInterval = mFireInterval;
}

void Weapon::SetAttackInterval(float interval)
{
	mFireInterval = interval;
}

void Weapon::InstantiateLaser()
{
	for (unsigned int idx = 0; idx < mCapacity; idx++) {
		Laser* laser = new Laser(mOwner->GetGame(), mIsEnemyLaser);
		laser->SetState(GameObject::State::EDeactive);
		laser->pTransform->SetScale(1.5f);
		mLasers.emplace_back(laser);
	}
}
