#pragma once

#include"include/GameObjectState.h"

class JumpState : public GameObjectState
{
public:
	JumpState();
	~JumpState();
	GameObjectState* HandleInput(class Hero* mOwner, const uint8_t * keyState) override;
	void Update(class Hero* mOwner) override;
	void Enter(class Hero* mOwner) override;
	void Exit() override;
private:
	float mMaxHeight;
	float mMaxTime;
	float mForce;
};

