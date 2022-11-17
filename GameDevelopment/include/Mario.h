#pragma once

#include "include/GameObject.h"
#include "include/ICooldownable.h"
#include<vector>
#include<memory>

class Weapon;

enum class Direction {
	Left,
	Right,
};

class Hero : public GameObject
{
public:
	Hero(class Game* game, const std::string& = "Hero");
	void UpdateGameObject(float deltaTime) override;
	void ProcessGameObjectInput(const uint8_t* keyState) override;
	bool IsMoving() const;
	void SetMoveDirection(Direction direction);
	class InputComponent* GetInputComponent() const;
	bool MoveExceedCenterPoint(bool toTheRight);
	bool IsImageFlipped();
	void Fire();
	// Components
	class InputComponent *inputComponent;
	class CircleComponent *circleComponent;
	class AnimatorComponent *animator;
	class RigidBodyComponent* rigidBodyComponent;
private:
	// Methods
	void StartCooldown();
	void ConstraintInScreenBounds();
	// Weapon
	std::unique_ptr<class Weapon> mWeapon;
	// States
	Vector2 mCenterPosition;
	class GameObjectState *mState;
};
