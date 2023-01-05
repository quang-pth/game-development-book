#pragma once

#include"include/GameObject.h"

class SplineGameObject : public GameObject
{
public:
	SplineGameObject(class Game* game, const std::string& name = "SplineGameObject");
	~SplineGameObject();
	void RestartSpline();
private:
	class SplineCamera* mCamera;
};

