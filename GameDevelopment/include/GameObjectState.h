#pragma once

#include <iostream>

class GameObjectState
{
public:
	virtual ~GameObjectState();
	virtual GameObjectState* HandleInput(class Hero* mario, const uint8_t* keyState) = 0;
	virtual void Update(class Hero* mOwner) = 0;
	virtual void Enter(class Hero* mOwner) = 0;
	virtual void Exit() = 0;
};

