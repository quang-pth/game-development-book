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
	Enemy(Game* game, int updateOrder = 30, const std::string& name = "Enemy");
	~Enemy();
	void UpdateGameObject(float deltaTime) override;
	virtual void Cooldown(float deltaTime);
private:
	AnimatorComponent* mAnimator;
	MoveComponent* mMoveComponent;
	SpriteComponent* mSpriteComponent;
	CircleComponent* mCircleComponent;
	AIComponent* mAI;
	std::vector<AIState*> mStates;
	AIState* mCurrentState;
};

