#pragma once

#include"include/DamagableState.h"

class Hero;

class WalkState : public DamagableState
{
public:
	WalkState() = default;
	WalkState(Hero* owner);
	~WalkState();
	void HandleInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	void Enter() override;
	void Exit() override;
};