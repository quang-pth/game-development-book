#pragma once

#include"include/GameObjectState.h"

class WalkState : public GameObjectState
{
public:
	~WalkState();
	GameObjectState* HandleInput(class Mario* mOwner, const uint8_t* keyState) override;
	void Update(class Mario* mOwner) override;
	void Enter(class Mario* mOwner) override;
	void Exit() override;
};