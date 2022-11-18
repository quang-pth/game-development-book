#pragma once

#include "include/GameObject.h"
#include "include/ICooldownable.h"
#include<vector>
#include<memory>
#include<unordered_map>

class Weapon;

enum class Direction {
	Left,
	Right,
};

class Hero : public GameObject
{
public:
	Hero() = default;
	Hero(class Game* game, const std::string& = "Hero");
	void UpdateGameObject(float deltaTime) override;
	void ProcessGameObjectInput(const uint8_t* keyState) override;
	bool IsMoving() const;
	void SetMoveDirection(Direction direction);
	class InputComponent* GetInputComponent() const;
	bool MoveExceedCenterPoint(bool toTheRight);
	bool IsImageFlipped();
	void Fire();
	bool IsAttacked() const;
	void SetIsAttacked(bool isAttacked);
	void ChangeState(const std::string& name);
	// Components
	class InputComponent *inputComponent;
	class CircleComponent *circleComponent;
	class AnimatorComponent *animator;
	class RigidBodyComponent* rigidBodyComponent;
private:
	// Methods
	void StartCooldown();
	void ConstraintInScreenBounds();
	// Combat
	std::unique_ptr<class Weapon> mWeapon;
	bool mIsAttacked;
	// States
	Vector2 mCenterPosition;
	class GameObjectState *mCurrentState;
	std::unordered_map<std::string, class GameObjectState*> mStateMap;
};
