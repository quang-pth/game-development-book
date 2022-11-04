#pragma once

#include"include/GameObjectState.h"

class IdleState : public GameObjectState
{
public:
	IdleState() = default;
	~IdleState();
	GameObjectState* HandleInput(class Hero* mOwner, const uint8_t* keyState) override;
	void Update(class Hero* mOwner) override;
	void Enter(class Hero* mOwner) override;
	void Exit() override;
};

