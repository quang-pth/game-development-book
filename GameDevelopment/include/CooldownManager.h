#pragma once

#include"include/GameObject.h"

class CooldownManager : public GameObject
{
public:
	CooldownManager();
	CooldownManager(class Game* game, std::string = "CooldownManager");
	~CooldownManager();
	void UpdateGameObject(float deltaTime) override;
	const void Observe(class ICooldownable* gameObject);
	const void Release(class ICooldownable* gameObject);
private:
	std::vector<class ICooldownable*> mCooldownableGameObjects;
	std::vector <std::vector<class ICooldownable*>::iterator> mDoneCooldownIters;
};

