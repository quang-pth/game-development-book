#include "AIComponent.h"
#include "include/GameObject.h"
#include "include/AIState.h"
#include <iostream>
#include <SDL2/SDL.h>

AIComponent::AIComponent(GameObject* owner, int updateOrder, const std::string& name) :
	Component(owner, updateOrder, name),
	mState()
{

}

AIComponent::~AIComponent()
{
	
}

void AIComponent::Update(float deltaTime)
{
	if (mState != nullptr) {
		mState->Update(deltaTime);
	}
}

void AIComponent::ChangeState(const std::string& name)
{
	if (mState != nullptr && mState->GetName() == name) return;

	// Exit the current state
	if (mState != nullptr) 
		mState->OnExit();
	// Transition to the next state if any
	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end()) {
		mState = iter->second;
		mState->OnEnter();
	}
	else {
		SDL_Log("Could not find AIState %s in the state map", name.c_str());
		mState = nullptr;
	}
}

void AIComponent::RegisterState(AIState* state)
{
	mStateMap.emplace(state->GetName(), state);
}

AIState* AIComponent::GetState() const
{
	return mState;
}

std::unordered_map<std::string, class AIState*> AIComponent::GetStates() const
{
	return mStateMap;
}