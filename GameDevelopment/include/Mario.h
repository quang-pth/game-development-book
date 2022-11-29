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
	bool IsDead() const;
	void SetMoveDirection(Direction direction);
	bool MoveExceedCenterPoint(bool toTheRight);
	bool IsImageFlipped();
	void Fire();
	void ReceiveDamage(float amount);
	bool IsAttacked() const;
	void SetIsAttacked(bool isAttacked);
	void ChangeState(const std::string& name);
protected:
	virtual void DeactivateGameObject() override;
public:
	class InputComponent* GetInputComponent() const;
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
	std::unique_ptr<class Health> mHealth;
	// States
	Vector2 mCenterPosition;
	class GameObjectState *mCurrentState;
	std::unordered_map<std::string, class GameObjectState*> mStateMap;
};
