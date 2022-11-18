#pragma once

#include"include/GameObjectState.h"

class Hero;

class HurtState : public GameObjectState
{
public:
	HurtState(Hero* owner);
	virtual ~HurtState();
	virtual void HandleInput(const uint8_t* keyState) override;
	virtual void Update(float deltaTime) override;
	virtual void Enter() override;
	virtual void Exit() override;
private:
	float mDuration;
};

