#pragma once

#include "include/AIState.h"

class AIInjured : public AIState
{
public:
	AIInjured(class AIComponent* owner);
	~AIInjured();
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;
	const char* GetName() const override;
private:
	const char* mName;
	float mDuration;
};

