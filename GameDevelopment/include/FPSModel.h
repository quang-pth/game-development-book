#pragma once

#include"include/GameObject.h"

class Game;
class MeshComponent;

class FPSModel : public GameObject
{
public:
	FPSModel(Game* game, const std::string& name = "FPSModel");
	~FPSModel();
	void SetVisible(bool visible);
private:
	MeshComponent* mMeshComponent;
};

