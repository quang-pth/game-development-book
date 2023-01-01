#pragma once

#include"include/GameObject.h"

class OrbitGameObject : public GameObject
{
public:
	OrbitGameObject(class Game* game, const std::string& name = "OrbitGameObject");
	~OrbitGameObject();
	virtual void ProcessGameObjectInput(const InputState& inputState) override;
	void SetVisible(bool visible);
private:
	class MeshComponent* mMeshComponent;
	class OrbitCamera* mCamera;
};

