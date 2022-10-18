#pragma once
#include "include/GameObject.h"
#include "include/ICooldownable.h"
#include<vector>

class Ship : public GameObject, ICooldownable
{
public:
	Ship(class Game* game);
	void UpdateGameObject(float deltaTime) override;
	void ProcessGameObjectInput(const uint8_t* keyState) override;
	void ActAfterCooldown() override;
private:
	// Methods
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
