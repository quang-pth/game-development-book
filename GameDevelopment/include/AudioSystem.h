#pragma once

#include<unordered_map>
#include<fmod_common.h>
#include"include/CustomMath.h"

// Forward declartions
namespace FMOD {
	class System;
	namespace Studio {
		class System;
		class Bank;
		class Bus;
		class EventDescription;
		class EventInstance;
	};
};

class SoundEvent;

FMOD_VECTOR VecToFMOD(const Vector3& vector);

class AudioSystem
{
public:
	static std::uint32_t sNextID;
public:
	AudioSystem(class Game* game);
	~AudioSystem();
	bool Initialize();
	SoundEvent PlayEvent(const std::string& name);
	float GetBusVolume(const std::string& name) const;
	bool GetBusPaused(const std::string& name) const;
	void SetBusVolume(const std::string& name, float value);
	void SetBusPause(const std::string& name, bool pause);
	void SetListener(const Matrix4& viewMatrix, const Vector3& offset = Vector3::Zero);
	void Shutdown();
	void Update(float deltaTime);
	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();
protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(const std::uint32_t& id) const;
private:
	void ReleaseEventInstances();
private:
	class Game* mGame;
	FMOD::Studio::System* mSystem;
	FMOD::System* mLowLevelSystem;
	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	std::unordered_map<std::uint32_t, FMOD::Studio::EventInstance*> mEventInstances;
	std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;
};