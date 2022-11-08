#pragma once

#include"include/AIState.h"

class AIPatrol : public AIState
{
public:
	AIPatrol(class AIComponent* owner);
	~AIPatrol();
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;
	const char* GetName() const override;
private:
	const char* mName;
};

