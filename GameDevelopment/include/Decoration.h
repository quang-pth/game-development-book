#pragma once

#include<include/GameObject.h>

class Decoration : public GameObject
{
public:
	Decoration(class Game* game, const std::string& name = "Decoration");
	~Decoration();
	class MeshComponent* GetMeshComponent() const { return mMeshComponent; }
private:
	class MeshComponent* mMeshComponent;
};

