#pragma once

#include"include/GameObject.h"

class Sphere : public GameObject
{
public:
	Sphere(class Game* game, const std::string& name = "Sphere");
	~Sphere();
	virtual void UpdateGameObject(float deltaTime) override;
private:
	class MeshComponent* mMeshComponent;
};

