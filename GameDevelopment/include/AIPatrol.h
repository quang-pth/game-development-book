#pragma once

#include"include/AIDamagable.h"
	
class AIPatrol : public AIDamagable
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

