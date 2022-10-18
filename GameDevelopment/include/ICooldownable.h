#pragma once

class ICooldownable
{
public:
	ICooldownable();
	ICooldownable(float cooldown);
	virtual void Cooldown(float deltaTime);
	virtual void ActAfterCooldown();
	void SetCooldown(float cooldown);
	float GetCooldown() const;
	void SetStartCooldown(bool startCooldown);
	bool CanCoolDown() const;
private:
	float mCooldown;
	bool mStartCooldown;
};

