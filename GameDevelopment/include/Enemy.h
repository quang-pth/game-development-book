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

class Enemy : public GameObject
{
public:
	Enemy() = default;
	Enemy(Game* game, const std::string& name = "Enemy");
	~Enemy();
	virtual void UpdateGameObject(float deltaTime) override;
	virtual void Cooldown(float deltaTime);
	CircleComponent* GetCircleComponent() const;
protected:
	AnimatorComponent* mAnimator;
	MoveComponent* mMoveComponent;
	SpriteComponent* mSpriteComponent;
	CircleComponent* mCircleComponent;
	AIComponent* mAI;
	std::vector<AIState*> mStates;
	AIState* mCurrentState;
};

