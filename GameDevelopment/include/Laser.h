#pragma once

#include"include/GameObject.h"

class MoveComponent;
class SpriteComponent;
class CircleComponent;

class Laser : public GameObject
{
public:
	Laser() = default;
	Laser(class Game* game, bool enemyLaser = false, const std::string& name = "Laser");
	void UpdateGameObject(float deltaTime) override;
	void SetDirection(int direction);
	void SetTexture(const std::string& filePath);
	MoveComponent* GetMoveComponent() const;
	SpriteComponent* GetSpriteComponent() const;
	CircleComponent* GetCircleComponent() const;
private:
	void CheckIsAlive();
	void ResetLaser();
	void CheckCollisions();
	MoveComponent* mMoveComponent;
	SpriteComponent* mSpriteComponent;
	CircleComponent* mCircleComponent;
	float mLifeTime;
	float mCurrentLifeTime;
	float mForwardSpeed;
	float mDamage;
	bool mIsEnemyLaser;
};