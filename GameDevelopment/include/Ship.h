#pragma once
#include "include/GameObject.h"
#include<vector>

class Ship : public GameObject
{
public:
	Ship(class Game* game);
	void UpdateGameObject(float deltaTime) override;
	void ProcessGameObjectInput(const uint8_t* keyState) override;
private:
	// Methods
	void InitLaserPool();
	// Weapon
	class std::vector<class Laser*> mLasers;
	unsigned int mActivateLaserIdx;
	float mFireCooldown;
	// Component
	class InputComponent* mInputComponent;
	class SpriteComponent* mSpriteComponent;
	uint8_t mFireKey;
};
