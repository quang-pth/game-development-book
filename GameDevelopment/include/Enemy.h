#pragma once

#include "include/GameObject.h"
#include<vector>
#include<memory>

class Game;
class AIState;
class AnimatorComponent;
class MoveComponent;
class SpriteComponent;
class CircleComponent;
class AIComponent;
class RigidBodyComponent;
class Health;
class Weapon;

class Enemy : public GameObject
{
public:
	Enemy() = default;
	Enemy(Game* game, const std::string& name = "Enemy");
	~Enemy();
	virtual void UpdateGameObject(float deltaTime) override;
	virtual void ActAsState(float deltaTime);
	virtual void ReceiveDamage(float amount);
	bool IsDead() const;
	CircleComponent* GetCircleComponent() const;
	MoveComponent* GetMoveComponent() const;
	AIComponent* GetAIComponent() const;
	AnimatorComponent* GetAnimatorComponent() const;
	RigidBodyComponent* GetRigidBodyComponent() const;
	float GetAttackRadius() const;
	bool IsAttacked() const;
	void SetIsAttacked(bool isAtacked);
	bool IsSawPlayer();
	bool IsNearPlayer();
protected:
	virtual void Patrol(float deltaTime);
	virtual void Attack(float deltaTime);
	virtual void Death(float deltaTime);
	// Components
	AnimatorComponent* mAnimator;
	MoveComponent* mMoveComponent;
	CircleComponent* mCircleComponent;
	AIComponent* mAI;
	RigidBodyComponent* mRigidBodyComponent;
	std::unique_ptr<Health> mHealth;
	std::unique_ptr<Weapon> mWeapon;
	// Other
	float mForwardSpeed;
	float mAttackRadius;
	bool mIsAttacked;
};

