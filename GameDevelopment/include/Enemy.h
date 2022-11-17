#pragma once

#include "include/GameObject.h"
#include<vector>

class Game;
class AIState;
class AnimatorComponent;
class MoveComponent;
class SpriteComponent;
class CircleComponent;
class AIComponent;
class Health;

class Enemy : public GameObject
{
public:
	Enemy() = default;
	Enemy(Game* game, const std::string& name = "Enemy");
	~Enemy();
	virtual void UpdateGameObject(float deltaTime) override;
	virtual void Cooldown(float deltaTime);
	virtual void ActAsState(float deltaTime);
	virtual void ReceiveDamage(float amount);
	CircleComponent* GetCircleComponent() const;
	MoveComponent* GetMoveComponent() const;
	AIComponent* GetAIComponent() const;
	AnimatorComponent* GetAnimatorComponent() const;
protected:
	// Components
	AnimatorComponent* mAnimator;
	MoveComponent* mMoveComponent;
	CircleComponent* mCircleComponent;
	AIComponent* mAI;
	Health* mHealth;
	// Other
	float mForwardSpeed;
	float mAttackRadius;
};

