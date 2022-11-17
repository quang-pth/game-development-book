#pragma once

#include "include/Enemy.h"

class OrchidOwl : public Enemy
{
public:
	OrchidOwl() = default;
	OrchidOwl(class Game* game, const std::string& name = "OrchidOwl");
	~OrchidOwl();
protected:
	virtual void Patrol(float deltaTime) override;
	virtual void Death(float deltaTime) override;
private:
	void ConstraintInBounds();
	void ChangeDirection();
	float mPatrolDuration, mCurrentPatrolTime;
};

