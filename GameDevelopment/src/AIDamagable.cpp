#include "include\AIDamagable.h"
#include "include\AnimatorComponent.h"
#include "include\AIComponent.h"
#include "include\Enemy.h"

AIDamagable::AIDamagable(AIComponent* owner) : 
    AIState(owner),
    mName("AIDamagable")
{
}

AIDamagable::~AIDamagable()
{
}

void AIDamagable::Update(float deltaTime)
{
    if (mAgent->IsAttacked()) {
        mOwner->ChangeState("AIInjured");
        return;
    }
}

void AIDamagable::OnEnter()
{

}

void AIDamagable::OnExit()
{
}

const char* AIDamagable::GetName() const
{
    return mName;
}
