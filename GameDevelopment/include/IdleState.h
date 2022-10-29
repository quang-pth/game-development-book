#pragma once

#include"include/GameObjectState.h"

class IdleState : public GameObjectState
{
public:
	IdleState() = default;
	~IdleState();
	GameObjectState* HandleInput(class Mario* mOwner, const uint8_t* keyState) override;
	void Update(class Mario* mOwner) override;
	void Enter(class Mario* mOwner) override;
	void Exit() override;
};

