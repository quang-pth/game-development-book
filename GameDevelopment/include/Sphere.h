#pragma once

#include"include/GameObject.h"
#include"include/SoundEvent.h"
#include"include/InputObserver.h"

class Sphere : public GameObject, InputObserver
{
public:
	Sphere(class Game* game, const std::string& name = "Sphere");
	~Sphere();
	virtual void UpdateGameObject(float deltaTime) override;
	virtual void OnNotify(class ControllerState* controller, InputObserver::Event inputEvent) override;
private:
	class MeshComponent* mMeshComponent;
	class AudioComponent* mAudioComponent;
	SoundEvent mGrassEvent;
};

