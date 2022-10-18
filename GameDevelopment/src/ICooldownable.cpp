#include "include/ICooldownable.h"

ICooldownable::ICooldownable() : mCooldown(0.0f), mStartCooldown(false)
{
}

ICooldownable::ICooldownable(float cooldown) : mCooldown(cooldown), mStartCooldown(false)
{
}

void ICooldownable::Cooldown(float deltaTime)
{
	mCooldown -= deltaTime;
	if (mCooldown <= 0.0f) {
		ActAfterCooldown();
	}
}

void ICooldownable::ActAfterCooldown()
{
}

void ICooldownable::SetCooldown(float cooldown)
{
	mCooldown = cooldown;
}

void ICooldownable::SetStartCooldown(bool startCooldown)
{
	mStartCooldown = startCooldown;
}

bool ICooldownable::CanCoolDown() const
{
	return mStartCooldown;
}

float ICooldownable::GetCooldown() const
{
	return mCooldown;
}
