#include "AIDeath.h"
#include "include/Enemy.h"
#include "include/GameObject.h"
#include "include/GameObject.h"
#include "include/GameObject.h"
#include "include/MoveComponent.h"
#include "include/AnimatorComponent.h"
#include "include/RigidBodyComponent.h"
#include "include/AIComponent.h"

AIDeath::AIDeath(AIComponent* owner) : 
	AIState(owner),
	mName("AIDeath"), mDuration(5.0f)
{
	mCurrentDuration = mDuration;
}

AIDeath::~AIDeath()
{
}

void AIDeath::Update(float deltaTime)
{
	mCurrentDuration -= deltaTime;
	mAgent->ActAsState(deltaTime);

	if (mCurrentDuration < 0.0f) {
		mOwner->GetOwner()->Deactivate();
		mCurrentDuration = mDuration;
	}
}

void AIDeath::OnEnter()
{
	mAgent->GetRigidBodyComponent()->WakeUp(true);
	mAgent->GetMoveComponent()->SetForwardSpeed(0.0f);
	mAgent->GetAnimatorComponent()->SetAnimation("Hurt");
}

void AIDeath::OnExit()
{
}

const char* AIDeath::GetName() const
{
	return mName;
}
