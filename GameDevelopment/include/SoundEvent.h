#pragma once

#include<cstdint>
#include<string>
#include"include/CustomMath.h"

namespace FMOD {
	namespace Studio {
		class EventInstance;
	}
}

class SoundEvent
{
public:
	SoundEvent() = default;
	~SoundEvent();
	bool IsValid();
	void Restart();
	void Stop(bool allowedFadeOut = true);
	void SetPaused(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);
	void Set3DAttributes(const Matrix4& worldTransformMatrix);
public:
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name) const;
	bool Is3D() const;
protected:
	friend class AudioSystem;
	SoundEvent(class AudioSystem* audioSystem, std::uint32_t id);
private:
	FMOD::Studio::EventInstance* GetEventInstance() const;
private:
	class AudioSystem* mAudioSystem;
	std::uint32_t mID;
};

