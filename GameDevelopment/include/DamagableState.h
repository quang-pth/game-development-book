#pragma once

#include"include/GameObjectState.h"

class DamagableState : public GameObjectState
{
public:
	DamagableState() = default;
	DamagableState(class Hero * owner);
	~DamagableState();
	void HandleInput(const uint8_t * keyState) override;
	void Update(float deltaTime) override;
	void Enter() override;
	void Exit() override;
};
