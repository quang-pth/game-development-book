#pragma once

#include <iostream>

class Hero;

class GameObjectState
{
public:
	GameObjectState(Hero* owner);
	virtual ~GameObjectState();
	virtual void HandleInput(const uint8_t* keyState) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
protected:
	Hero* mOwner;
};

