#pragma once

#include"include/Component.h"
#include<vector>

class SoundEvent;

class AudioComponent : public Component
{
public:
	AudioComponent(class GameObject* owner, int updateOrder = 200, const std::string& name = "AudioComponent");
	~AudioComponent();
	virtual void Update(float deltaTime) override;
	virtual void OnUpdateWorldTransform() override;
	SoundEvent PlayEvent(const std::string& name);
	void StopAllEvents();
private:
	void ClearEvents(std::vector<SoundEvent>& events);
private:
	std::vector<SoundEvent> mEvents2D;
	std::vector<SoundEvent> mEvents3D;
};

