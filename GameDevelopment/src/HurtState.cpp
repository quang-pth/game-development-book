#include "HurtState.h"
#include "include/Mario.h"
#include "include/IdleState.h"
#include "include/AnimatorComponent.h"

HurtState::HurtState(Hero* owner) :
    GameObjectState(owner),
    mDuration(.25f)
{

}

HurtState::~HurtState()
{
}

void HurtState::HandleInput(const uint8_t* keyState)
{
    if (mDuration > 0) return;

    mOwner->ChangeState("IdleState");
}

void HurtState::Update(float deltaTime)
{
    mDuration -= deltaTime;
}

void HurtState::Enter()
{
    mOwner->animator->SetAnimation("Hurt");
}

void HurtState::Exit()
{
    mDuration = .25f;
    mOwner->SetIsAttacked(false);
}
