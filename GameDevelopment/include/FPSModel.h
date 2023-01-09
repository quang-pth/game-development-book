#pragma once

#include"include/GameObject.h"

class Game;
class MeshComponent;
class BoxComponent;

class FPSModel : public GameObject
{
public:
	FPSModel(Game* game, const std::string& name = "FPSModel");
	~FPSModel();
	void SetVisible(bool visible);
	MeshComponent* GetMeshComponent() const { return mMeshComponent; }
	BoxComponent* GetBoxComponent() const { return mBoxComponent; }
private:
	MeshComponent* mMeshComponent;
	BoxComponent* mBoxComponent;
};

