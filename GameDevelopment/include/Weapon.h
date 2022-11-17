#pragma once

#include "include/MoveComponent.h"

class Laser;
class GameObject;

class Weapon
{
public:
	Weapon() = default;
	Weapon(GameObject* mOwner, bool isEnemyLaser = false);
	~Weapon();
	void Update(float deltaTime);
	void Fire();
	void SetAttackInterval(float interval);
private:
	void InstantiateLaser();
	GameObject* mOwner;
	float mFireInterval;
	float mCurrentFireInterval;
	unsigned int mActivateLaserIdx;
	unsigned int mCapacity;
	Direction mFireDirection;
	std::vector<class Laser*> mLasers;
	bool mIsEnemyLaser;
};