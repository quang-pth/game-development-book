#pragma once

#include "include/GameObject.h"
#include "include/ICooldownable.h"
#include<vector>

class Mario : public GameObject, ICooldownable
{
public:
	Mario(class Game* game);
	void UpdateGameObject(float deltaTime) override;
	void ProcessGameObjectInput(const uint8_t* keyState) override;
	void Cooldown(float deltaTime) override;
private:
	// Methods
	void StartCooldown();
	void ActAfterCooldown();
	void InitLaserPool();
	void ConstraintInScreenBounds();
	void CheckCollsision();
	// Weapon
	class std::vector<class Laser*> mLasers;
	unsigned int mActivateLaserIdx;
	// Cooldown
	float mFireCooldown;
	float mSpawnCooldown;
	// Component
	class InputComponent* mInputComponent;
	class SpriteComponent* mSpriteComponent;
	class CircleComponent* mCircleComponent;
	uint8_t mFireKey;
};
