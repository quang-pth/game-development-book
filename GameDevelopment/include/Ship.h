#pragma once

#include "include/GameObject.h"
#include "include/ICooldownable.h"
#include"include/InputSystem.h"
#include<vector>

class Ship : public GameObject, ICooldownable
{
public:
	Ship(class Game* game);
	void UpdateGameObject(float deltaTime) override;
	void ProcessGameObjectInput(const InputState& keyState) override;
	void Cooldown(float deltaTime) override;
private:
	// Methods
	void StartCooldown();
	void Respawn();
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
