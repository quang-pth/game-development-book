#include "IdleState.h"
#include "include/Mario.h"
#include "include/InputComponent.h"
#include "include/AnimatorComponent.h"
#include "include/WalkState.h"

IdleState::~IdleState()
{
}

GameObjectState* IdleState::HandleInput(Mario* mOwner, const uint8_t* keyState)
{
	bool isWalked = keyState[mOwner->mInputComponent->GetForwardLeftKey()]
		|| keyState[mOwner->mInputComponent->GetForwardRightKey()];
	
	if (isWalked) {
		return new WalkState();
	}

    return nullptr;
}

void IdleState::Update(Mario* mOwner)
{
}

void IdleState::Enter(Mario* mOwner)
{
	mOwner->mAnimator->SetAnimation("Idle");
}

void IdleState::Exit()
{
}
