#pragma once
#include "include/GameObject.h"

class Ship : public GameObject
{
public:
	Ship(class Game* game);
	void UpdateGameObject(float deltaTime) override;
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
private:
	float mRightSpeed;
	float mDownSpeed;
	class InputComponent* mInputComponent;
	class SpriteComponent* mSpriteComponent;
};
