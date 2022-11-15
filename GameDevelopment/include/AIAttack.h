#pragma once

#include "include/AIState.h"

class AIAttack : public AIState
{
public:
	AIAttack(class AIComponent* owner);
	~AIAttack();
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;
	const char* GetName() const override;
private:
	const char* mName;
};

