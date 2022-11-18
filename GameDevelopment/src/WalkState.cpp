#include "include/WalkState.h"
#include "include/Mario.h"
#include "include/InputComponent.h"
#include "include/AnimatorComponent.h"
#include "include/JumpState.h"
#include "include/IdleState.h"

WalkState::WalkState(Hero* owner) : DamagableState(owner)
{

}

WalkState::~WalkState()
{
}

void WalkState::HandleInput(const uint8_t* keyState)
{
	DamagableState::HandleInput(keyState);

	bool remainInWalkState = keyState[mOwner->inputComponent->GetInputKey("Left")]
		|| keyState[mOwner->inputComponent->GetInputKey("Right")];

	if (keyState[mOwner->inputComponent->GetInputKey("Jump")]) {
		mOwner->ChangeState("JumpState");
	}

	if (remainInWalkState) {
		return;
	}

	mOwner->ChangeState("IdleState");
}

void WalkState::Update(float deltaTime)
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

void WalkState::Enter()
{
	mOwner->animator->FlipTexture(mOwner->IsImageFlipped());
	mOwner->animator->SetAnimation("Walk");
}

void WalkState::Exit()
{
}
