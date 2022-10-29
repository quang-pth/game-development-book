#pragma once

#include "include/GameObject.h"
#include "include/ICooldownable.h"
#include<vector>

class Mario : public GameObject, ICooldownable
{
public:
	enum class Direction {
		Left,
		Right,
	};
	Mario(class Game* game, std::string = "Mario");
	void UpdateGameObject(float deltaTime) override;
	void ProcessGameObjectInput(const uint8_t* keyState) override;
	void Cooldown(float deltaTime) override;
	Direction GetMoveDirection() const;
	void SetMoveDirection(bool toTheRight);
	class InputComponent* GetInputComponent() const;
	bool MoveExceedCenterPoint(bool toTheRight);
	bool IsImageFlipped();
	// Components
	class InputComponent *pInputComponent;
	class CircleComponent *pCircleComponent;
	class AnimatorComponent *pAnimator;
private:
	// Methods
	void StartCooldown();
	void ActAfterCooldown();
	void ConstraintInScreenBounds();
	// Weapon
	unsigned int mActivateLaserIdx;
	// Cooldown
	float mFireCooldown;
	float mSpawnCooldown;
	// Component
	uint8_t mFireKey;
	// States
	Direction mMoveDirection;
	Vector2 mCenterPosition;
	class GameObjectState *mpState;
};
