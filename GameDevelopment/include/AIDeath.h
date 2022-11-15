#pragma once

#include "include/AIState.h"

class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* owner);
	~AIDeath();
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;
	const char* GetName() const override;
private:
	const char* mName;
};

