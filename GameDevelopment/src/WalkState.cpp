#include "include/WalkState.h"
#include "include/Mario.h"
#include "include/InputComponent.h"
#include "include/AnimatorComponent.h"
#include "include/JumpState.h"
#include "include/IdleState.h"

WalkState::~WalkState()
{
}

GameObjectState* WalkState::HandleInput(Hero* mOwner, const uint8_t* keyState)
{
	bool remainInWalkState = keyState[mOwner->inputComponent->GetInputKey("Left")]
		|| keyState[mOwner->inputComponent->GetInputKey("Right")];
	
	if (keyState[mOwner->inputComponent->GetInputKey("Jump")]) {
		return new JumpState();
	}

	if (remainInWalkState) {
		return nullptr;
	}

	return new IdleState();
}

void WalkState::Update(Hero* mOwner)
{
	if (mOwner->inputComponent->RightKeyIsClicked()) {
		mOwner->SetMoveDirection(Direction::Right);
		mOwner->animator->FlipTexture(false);
	}
	else {
		mOwner->SetMoveDirection(Direction::Left);
		mOwner->animator->FlipTexture(true);
	}
}

void WalkState::Enter(Hero* mOwner)
{
	mOwner->animator->FlipTexture(mOwner->IsImageFlipped());
	mOwner->animator->SetAnimation("Walk");
}

void WalkState::Exit()
{
}
