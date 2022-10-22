#include "include/CooldownManager.h"
#include "include/ICooldownable.h"

CooldownManager::CooldownManager() : 
	GameObject(), mCooldownableGameObjects()
{
}

CooldownManager::CooldownManager(Game* game, std::string name) :
	GameObject(game, name), mCooldownableGameObjects()
{
}

CooldownManager::~CooldownManager()
{
}

void CooldownManager::UpdateGameObject(float deltaTime)
{
	for (ICooldownable* gameObject : mCooldownableGameObjects) {
		gameObject->Cooldown(deltaTime);
	}
	for (std::vector<ICooldownable*>::iterator iter : mDoneCooldownIters) {
		mCooldownableGameObjects.erase(iter);
	}
	mDoneCooldownIters.clear();
}

const void CooldownManager::Observe(ICooldownable* gameObject)
{
	if (gameObject != nullptr) {
		mCooldownableGameObjects.emplace_back(gameObject);
	}
}

const void CooldownManager::Release(ICooldownable* gameObject)
{
	std::vector<ICooldownable*>::iterator iter = std::find(mCooldownableGameObjects.begin(),
		mCooldownableGameObjects.end(), gameObject);
	if (iter != mCooldownableGameObjects.end()) {
		mDoneCooldownIters.emplace_back(iter);
	}
}
