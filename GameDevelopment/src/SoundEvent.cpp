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
	return mAudioSystem && this->GetEventInstance();
}

void SoundEvent::Restart()
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	if (e) {
		e->start();
	}
}

void SoundEvent::Stop(bool allowedFadeOut)
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	if (e) {
		FMOD_STUDIO_STOP_MODE mode = allowedFadeOut ? FMOD_STUDIO_STOP_ALLOWFADEOUT : FMOD_STUDIO_STOP_IMMEDIATE;
		e->stop(mode);
	}
}

void SoundEvent::SetPaused(bool pause)
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	if (e) {
		e->setPaused(pause);
	}
}

void SoundEvent::SetVolume(float value)
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	if (e) {
		e->setVolume(value);
	}
}

void SoundEvent::SetPitch(float value)
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	if (e) {
		e->setPitch(value);
	}
}

void SoundEvent::SetParameter(const std::string& name, float value)
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	if (e) {
		e->setParameterValue(name.c_str(), value);
	}
}

void SoundEvent::Set3DAttributes(const Matrix4& worldTransformMatrix)
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	if (e) {
		FMOD_3D_ATTRIBUTES attributes;
		attributes.position = VecToFMOD(worldTransformMatrix.GetTranslation());
		attributes.forward = VecToFMOD(worldTransformMatrix.GetXAxis());
		attributes.up = VecToFMOD(worldTransformMatrix.GetZAxis());
		attributes.velocity = { 0.0f };
		e->set3DAttributes(&attributes);
	}
}

bool SoundEvent::GetPaused() const
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	bool paused = true;
	if (e) {
		e->getPaused(&paused);
	}
	return paused;
}

float SoundEvent::GetVolume() const
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	float volume = 0.0f;
	if (e) {
		e->getVolume(&volume);
	}
	return volume;
}

float SoundEvent::GetPitch() const
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	float pitch = 0.0f;
	if (e) {
		e->getPitch(&pitch);
	}
	return pitch;
}

float SoundEvent::GetParameter(const std::string& name) const
{
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	float value = 0.0f;
	if (e) {
		e->getParameterValue(name.c_str(), &value);
	}
	return value;
}

bool SoundEvent::Is3D() const
{
	bool is3D = false;
	FMOD::Studio::EventInstance* e = this->GetEventInstance();
	if (e) {
		FMOD::Studio::EventDescription* eventDescription = nullptr;
		e->getDescription(&eventDescription);
		if (eventDescription) {
			eventDescription->is3D(&is3D);
		}
	}
	return is3D;
}

FMOD::Studio::EventInstance* SoundEvent::GetEventInstance() const
{
	return mAudioSystem ? mAudioSystem->GetEventInstance(mID) : nullptr;
}
