#pragma once

#include"include/GameObject.h"

class CooldownManager : public GameObject
{
public:
	CooldownManager();
	CooldownManager(class Game* game, std::string = "CooldownManager");
	~CooldownManager();
	void UpdateGameObject(float deltaTime) override;
	const void Subscribe(class ICooldownable* iCooldownable);
	const void UnSubscribe(class ICooldownable* iCooldownable);
private:
	std::vector<class ICooldownable*> mCooldownableGameObjects;
	std::vector <std::vector<ICooldownable*>::iterator> mDoneCooldownIters;
	bool mIsUpdating;
};

