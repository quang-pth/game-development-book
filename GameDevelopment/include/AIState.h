#pragma once

class AIState
{
public:
	AIState(class AIComponent* owner);
	virtual ~AIState();
	virtual void Update(float deltaTime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual const char* GetName() const = 0;
	bool CanAttack() const;
protected:
	class AIComponent* mOwner;
	class Enemy* mAgent;
};

