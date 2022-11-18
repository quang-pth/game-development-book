#pragma once

#include "include/Enemy.h"

class Martian : public Enemy
{
public:
	Martian() = default;
	Martian(class Game* game, const std::string& name = "Martian");
	~Martian();
protected:
	virtual void Patrol(float deltaTime) override;
	virtual void Death(float deltaTime) override;
private:
	void ConstraintInBounds();
	void ChangeDirection();
	float mPatrolDuration, mCurrentPatrolTime;
};

