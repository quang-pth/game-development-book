#pragma once

#include"include/GameObject.h"

class Laser : public GameObject
{
public:
	Laser() = default;
	Laser(class Game* game, const std::string& name = "Laser");
	void UpdateGameObject(float deltaTime) override;
	void SetDirection(int direction);
	void SetTexture(const std::string& filePath);
	class MoveComponent* GetMoveComponent() const;
	class SpriteComponent* GetSpriteComponent() const;
	class CircleComponent* GetCircleComponent() const;
private:
	void CheckIsAlive();
	void ResetLaser();
	void CheckCollisions();
	class MoveComponent* mMoveComponent;
	class SpriteComponent* mSpriteComponent;
	class CircleComponent* mCircleComponent;
	float mLifeTime;
	float mCurrentLifeTime;
	float mForwardSpeed;
	float mDamage;
};

