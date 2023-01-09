#pragma once

#include<include/GameObject.h>

class Decoration : public GameObject
{
public:
	Decoration(class Game* game, const std::string& name = "Decoration");
	~Decoration();
	class MeshComponent* GetMeshComponent() const { return mMeshComponent; }
	class BoxComponent* GetBoxComponent() const { return mBoxComponent; }
private:
	class MeshComponent* mMeshComponent;
	class BoxComponent* mBoxComponent;
};

