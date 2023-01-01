#pragma once

#include"include/GameObject.h"

class SplineGameObject : public GameObject
{
public:
	SplineGameObject(class Game* game, const std::string& name = "SplineGameObject");
	~SplineGameObject();
	virtual void ProcessGameObjectInput(const InputState& inputState);
	void RestartSpline();
private:
	class SplineCamera* mCamera;
};

