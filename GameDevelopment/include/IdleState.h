#pragma once

#include"include/DamagableState.h"

class Hero;

class IdleState : public DamagableState
{
public:
	IdleState() = default;
	IdleState(Hero* owner);
	~IdleState();
	void HandleInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	void Enter() override;
	void Exit() override;
};

