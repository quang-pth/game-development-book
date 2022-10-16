#pragma once

#include"include/GameObject.h"

class Laser : public GameObject
{
public:
	Laser();
	Laser(class Game* game, std::string name = "Laser");
	void UpdateGameObject(float deltaTime) override;
	class MoveComponent* GetMoveComponent() const;
	class SpriteComponent* GetSpriteComponent() const;
	class CircleComponent* GetCircleComponent() const;
private:
	class MoveComponent* mMoveComponent;
	class SpriteComponent* mSpriteComponent;
	class CircleComponent* mCircleComponent;
};

