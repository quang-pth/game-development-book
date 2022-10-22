#pragma once
#include "include/GameObject.h"

class Mario : public GameObject
{
public:
	Mario(class Game* game);
	void UpdateGameObject(float deltaTime) override;
	void ProcesKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
private:
	float mRightSpeed;
	float mDownSpeed;
	class AnimatorComponent* mAnimator;
};
