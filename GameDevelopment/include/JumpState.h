#pragma once

#include"include/DamagableState.h"

class Hero;

class JumpState : public DamagableState
{
public:
	JumpState() = default;
	JumpState(Hero* owner);
	~JumpState();
	void HandleInput(const uint8_t * keyState) override;
	void Update(float deltaTime) override;
	void Enter() override;
	void Exit() override;
private:
	float mMaxHeight;
	float mMaxTime;
	float mForce;
};

