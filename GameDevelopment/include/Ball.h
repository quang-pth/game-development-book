#pragma once

#include"include/GameObject.h"

class Ball : public GameObject 
{
public:
	Ball(class Game* game, const std::string& name = "Ball");
	virtual void UpdateGameObject(float deltaTime) override;
	virtual void Activate() override;
	virtual void Deactivate() override;
	void Fire(const Vector3& startPos, const Vector3& fireDirection);
	class BallMoveComponent* GetBallMoveComponent() const { return mBallMoveComponent; }
private:
	float mDistance;
	class BallMoveComponent* mBallMoveComponent;
	class MeshComponent* mMeshComponent;
	class BoxComponent* mBoxComponent;
};

