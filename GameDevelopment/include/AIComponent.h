#pragma once

#include"include/Component.h"
#include<unordered_map>

class AIComponent : public Component
{
public:
	AIComponent(class GameObject* owner, int updateOrder = 20, const std::string& name = "AIComponent");
	~AIComponent();
	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);
	void RegisterState(class AIState* state);
	AIState* GetState() const;
	std::unordered_map<std::string, class AIState*> GetStates() const;
private:
	std::unordered_map<std::string, class AIState*> mStateMap;
	class AIState* mState;
};

