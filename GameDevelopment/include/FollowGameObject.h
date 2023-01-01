#pragma once

#include"include/GameObject.h"

class FollowGameObject : public GameObject
{
public:
	FollowGameObject(class Game* game, const std::string& name = "FollowGameObject");
	~FollowGameObject();
	void SetVisible(bool visible);
private:
	class InputComponent* mInputComponent;
	class MeshComponent* mMeshComponent;
	class FollowCamera* mCamera;
};

