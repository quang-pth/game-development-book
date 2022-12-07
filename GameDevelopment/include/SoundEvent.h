#pragma once

#include <cstdint>
#include<string>

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
public:
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name) const;
protected:
	friend class AudioSystem;
	SoundEvent(class AudioSystem* audioSystem, std::uint32_t id);
private:
	class AudioSystem* mAudioSystem;
	std::uint32_t mID;
};

