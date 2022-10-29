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
	bool remainInWalkState = keyState[mOwner->mInputComponent->GetForwardLeftKey()] || keyState[mOwner->mInputComponent->GetForwardRightKey()];
	
	if (remainInWalkState) {
		return nullptr;
	}

	return new IdleState();
}

void WalkState::Update(class Mario* mOwner)
{
	if (mOwner->mInputComponent->RightKeyIsClicked()) {
		mOwner->SetMoveDirection(true);
		mOwner->mAnimator->FlipTexture(true);
	}
	else {
		mOwner->SetMoveDirection(false);
		mOwner->mAnimator->FlipTexture(false);
	}
}

void WalkState::Enter(Mario* mOwner)
{
	mOwner->mAnimator->FlipTexture(mOwner->FlipImage());
	mOwner->mAnimator->SetAnimation("Walk");
}

void WalkState::Exit()
{
}
