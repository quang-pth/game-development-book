#pragma once

#include "include/Enemy.h"

class OrchidOwl : public Enemy
{
public:
	OrchidOwl() = default;
	OrchidOwl(class Game* game, const std::string& name = "OrchidOwl");
	~OrchidOwl();
	virtual void UpdateGameObject(float deltaTime) override;
	virtual void ActAsState(float deltaTime) override;
private:
	void Patrol(float deltaTime);
	void Attack(float deltaTime);
	void Death(float deltaTime);
	float mPatrolDuration, mCurrentPatrolTime;
};

