#pragma once

#include"include/GameObject.h"

class Cube : public GameObject
{
public:
	Cube(class Game* game, const std::string& name = "Cube");
	~Cube();
	virtual void UpdateGameObject(float deltaTime) override;
private:
	class MeshComponent* mMesh;
};

