#pragma once

#include "include/Enemy.h"

class MrCircuit : public Enemy
{
public:
	MrCircuit() = default;
	MrCircuit(class Game* game, const std::string& name = "Martian");
	~MrCircuit();
protected:
	virtual void Patrol(float deltaTime) override;
	virtual void Death(float deltaTime) override;
private:
	void ConstraintInBounds();
	void ChangeDirection();
	float mPatrolDuration, mCurrentPatrolTime;
};

