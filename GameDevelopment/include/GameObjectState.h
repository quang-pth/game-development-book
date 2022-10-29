#pragma once

#include <iostream>

class GameObjectState
{
public:
	virtual ~GameObjectState();
	virtual GameObjectState* HandleInput(class Mario* mario, const uint8_t* keyState) = 0;
	virtual void Update(class Mario* mOwner) = 0;
	virtual void Enter(class Mario* mOwner) = 0;
	virtual void Exit() = 0;
};

