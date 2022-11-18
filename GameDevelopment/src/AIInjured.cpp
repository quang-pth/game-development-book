#include "include/AIInjured.h"
#include "include/AIComponent.h"
#include "include/AnimatorComponent.h"
#include "include/Enemy.h"

AIInjured::AIInjured(AIComponent* owner) : 
    AIState(owner), mName("AIInjured"),
    mDuration(0.4f)
{
}

AIInjured::~AIInjured()
{
}

void AIInjured::Update(float deltaTime)
{
    mDuration -= deltaTime;
    if (mDuration > 0) return;

    mOwner->ChangeState("AIPatrol");
}

void AIInjured::OnEnter()
{
    mAgent->GetAnimatorComponent()->SetAnimation("Hurt");
}

void AIInjured::OnExit()
{
    mDuration = 0.4f;
    mAgent->SetIsAttacked(false);
}

const char* AIInjured::GetName() const
{
    return "AIInjured";
}
