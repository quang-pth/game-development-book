#include "include/CooldownManager.h"
#include "include/ICooldownable.h"

CooldownManager::CooldownManager() : 
	GameObject(), mCooldownableGameObjects(), mIsUpdating(false)
{
}

CooldownManager::CooldownManager(Game* game, std::string name) :
	GameObject(game, name), mCooldownableGameObjects(), mIsUpdating(false)
{
}

CooldownManager::~CooldownManager()
{
}

void CooldownManager::UpdateGameObject(float deltaTime)
{
	for (ICooldownable* gameObject : mCooldownableGameObjects) {
		if (gameObject->CanCoolDown()) {
			gameObject->Cooldown(deltaTime);
		}
	}
	for (std::vector<ICooldownable*>::iterator iter : mDoneCooldownIters) {
		mCooldownableGameObjects.erase(iter);
	}
	mDoneCooldownIters.clear();
}

const void CooldownManager::Subscribe(ICooldownable* iCooldownable)
{
	mCooldownableGameObjects.emplace_back(iCooldownable);
}

const void CooldownManager::UnSubscribe(ICooldownable* iCooldownable)
{
	std::vector<ICooldownable*>::iterator iter = std::find(mCooldownableGameObjects.begin(),
		mCooldownableGameObjects.end(), iCooldownable);
	if (iter != mCooldownableGameObjects.end()) {
		mDoneCooldownIters.emplace_back(iter);
	}
}
