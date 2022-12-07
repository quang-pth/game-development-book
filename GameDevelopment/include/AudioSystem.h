#pragma once

#include<unordered_map>
#include"include/CustomMath.h"
#include<fmod_common.h>

// Forward declartions
namespace FMOD {
	class System;
	namespace Studio {
		class System;
		class Bank;
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
	void SetListener(const Matrix4& viewMatrix);
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
};