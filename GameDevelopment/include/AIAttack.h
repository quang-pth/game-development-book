#pragma once

#include "include/AIDamagable.h"

class AIAttack : public AIDamagable
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
	float mRemainingDuration;
};

