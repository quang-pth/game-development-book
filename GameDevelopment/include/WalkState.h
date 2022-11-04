#pragma once

#include"include/GameObjectState.h"

class WalkState : public GameObjectState
{
public:
	~WalkState();
	GameObjectState* HandleInput(class Hero* mOwner, const uint8_t* keyState) override;
	void Update(class Hero* mOwner) override;
	void Enter(class Hero* mOwner) override;
	void Exit() override;
};