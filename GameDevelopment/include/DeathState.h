#pragma once

#include"include/GameObjectState.h"

class Hero;

class DeathState: public GameObjectState
{
public:
	DeathState() = default;
	DeathState(Hero* owner);
	~DeathState();
	void HandleInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;
	void Enter() override;
	void Exit() override;
private:
	float mDuration;
};