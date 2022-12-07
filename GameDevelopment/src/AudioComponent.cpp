#include "include/AudioComponent.h"
#include "include/Game.h"
#include "include/GameObject.h"
#include "include/AudioSystem.h"
#include "include/SoundEvent.h"
#include "include/TransformComponent.h"

AudioComponent::AudioComponent(GameObject* owner, int updateOrder, const std::string& name) :
	Component(owner, updateOrder, name)
{
}

AudioComponent::~AudioComponent()
{
	this->StopAllEvents();
}

void AudioComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);
	this->ClearEvents(mEvents3D);
	this->ClearEvents(mEvents2D);
}

void AudioComponent::OnUpdateWorldTransform()
{
	for (SoundEvent& soundEvent : mEvents3D) {
		if (soundEvent.IsValid()) {
			soundEvent.Set3DAttributes(mOwner->GetTransform()->GetWorldTransformMatrix());
		}
	}
}

SoundEvent AudioComponent::PlayEvent(const std::string& name)
{
	SoundEvent soundEvent = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
	if (soundEvent.Is3D()) {
		mEvents3D.emplace_back(soundEvent);
		soundEvent.Set3DAttributes(mOwner->GetTransform()->GetWorldTransformMatrix());
	}
	else {
		mEvents2D.emplace_back(soundEvent);
	}
	return soundEvent;
}

void AudioComponent::StopAllEvents()
{
	for (SoundEvent& soundEvent : mEvents3D) {
		soundEvent.Stop();
	}
	mEvents3D.clear();
	for (SoundEvent& soundEvent : mEvents2D) {
		soundEvent.Stop();
	}
	mEvents2D.clear();
}

// Remove invalid sound event
void AudioComponent::ClearEvents(std::vector<SoundEvent>& events)
{
	auto iter = events.begin();
	while (iter != events.end()) {
		if (!iter->IsValid()) {
			events.erase(iter);
		}
		else {
			++iter;
		}
	}
}
