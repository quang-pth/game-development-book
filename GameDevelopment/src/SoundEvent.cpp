#include "include/SoundEvent.h"
#include "include/AudioSystem.h"
#include<fmod_studio.hpp>

SoundEvent::SoundEvent(AudioSystem* audioSystem, std::uint32_t id) :
	mAudioSystem(audioSystem), mID(id)
{
}

SoundEvent::~SoundEvent()
{
}

bool SoundEvent::IsValid()
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	return mAudioSystem && e;
}

void SoundEvent::Restart()
{

}

void SoundEvent::Stop(bool allowedFadeOut)
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	if (e) {
		FMOD_STUDIO_STOP_MODE mode = allowedFadeOut ? FMOD_STUDIO_STOP_ALLOWFADEOUT : FMOD_STUDIO_STOP_IMMEDIATE;
		e->stop(mode);
	}
}

void SoundEvent::SetPaused(bool pause)
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	if (e) {
		e->setPaused(pause);
	}
}

void SoundEvent::SetVolume(float value)
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	if (e) {
		e->setVolume(value);
	}
}

void SoundEvent::SetPitch(float value)
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	if (e) {
		e->setPitch(value);
	}
}

void SoundEvent::SetParameter(const std::string& name, float value)
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	if (e) {
		e->setParameterValue(name.c_str(), value);
	}
}

bool SoundEvent::GetPaused() const
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	bool paused = true;
	if (e) {
		e->getPaused(&paused);
	}
	return paused;
}

float SoundEvent::GetVolume() const
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	float volume = 0.0f;
	if (e) {
		e->getVolume(&volume);
	}
	return volume;
}

float SoundEvent::GetPitch() const
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	float pitch = 0.0f;
	if (e) {
		e->getPitch(&pitch);
	}
	return pitch;
}

float SoundEvent::GetParameter(const std::string& name) const
{
	FMOD::Studio::EventInstance* e = mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
	float value = 0.0f;
	if (e) {
		e->getParameterValue(name.c_str(), &value);
	}
	return value;
}
