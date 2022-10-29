#include "include/WalkState.h"
#include "include/Mario.h"
#include "include/InputComponent.h"
#include "include/AnimatorComponent.h"
#include "include/IdleState.h"

WalkState::~WalkState()
{
}

GameObjectState* WalkState::HandleInput(Mario* mOwner, const uint8_t* keyState)
{
	bool remainInWalkState = keyState[mOwner->pInputComponent->GetForwardLeftKey()] || keyState[mOwner->pInputComponent->GetForwardRightKey()];
	
	if (remainInWalkState) {
		return nullptr;
	}

	return new IdleState();
}

void WalkState::Update(class Mario* mOwner)
{
	if (mOwner->pInputComponent->RightKeyIsClicked()) {
		mOwner->SetMoveDirection(true);
		mOwner->pAnimator->FlipTexture(true);
	}
	else {
		mOwner->SetMoveDirection(false);
		mOwner->pAnimator->FlipTexture(false);
	}
}

void WalkState::Enter(Mario* mOwner)
{
	mOwner->pAnimator->FlipTexture(mOwner->IsImageFlipped());
	mOwner->pAnimator->SetAnimation("Walk");
}

void WalkState::Exit()
{
}
