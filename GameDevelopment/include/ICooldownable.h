#pragma once

class ICooldownable
{
public:
	virtual void Cooldown(float deltaTime) = 0;
};

