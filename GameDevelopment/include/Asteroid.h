#pragma once

#include "include/GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid(class Game *game, std::string = "Asteriod");
	~Asteroid();
	void UpdateGameObject(float deltaTime) override;
	class MoveComponent* GetMoveComponent() const;
	class SpriteComponent* GetSpriteComponent() const;
	class CircleComponent* GetCircleComponent() const;
private:
	class MoveComponent* mMoveComponent;
	class SpriteComponent* mSpriteComponent;
	class CircleComponent* mCircleComponent;
};

