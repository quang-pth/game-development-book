#pragma once

#include "include/GameObject.h"
#include "include/ICooldownable.h"
#include<vector>

enum class Direction {
	Left,
	Right,
};

class Hero : public GameObject, ICooldownable
{
public:
	Hero(class Game* game, std::string = "Mario");
	void UpdateGameObject(float deltaTime) override;
	void ProcessGameObjectInput(const uint8_t* keyState) override;
	void Cooldown(float deltaTime) override;
	void SetDirection(Direction direction);
	void Fire();
	bool IsMoving() const;
	Direction GetMoveDirection() const;
	void SetMoveDirection(Direction direction);
	class InputComponent* GetInputComponent() const;
	bool MoveExceedCenterPoint(bool toTheRight);
	bool IsImageFlipped();
	// Components
	class InputComponent *inputComponent;
	class CircleComponent *circleComponent;
	class AnimatorComponent *animator;
	class RigidBodyComponent* rigidBodyComponent;
private:
	// Methods
	void StartCooldown();
	void ActAfterCooldown();
	void ConstraintInScreenBounds();
	void InstantiateLaser();
	// Weapon
	float mSpawnCooldown;
	float mFireCooldown;
	float mCurrentFireCooldown;
	unsigned int mActivateLaserIdx;
	unsigned int mCapacity;
	Direction mFireDirection;
	std::vector<class Laser*> mLasers;
	// States
	Direction mMoveDirection;
	Vector2 mCenterPosition;
	class GameObjectState *mState;
};
