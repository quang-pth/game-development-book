#include "include/AudioSystem.h"
#include "include/Game.h"
#include "include/SoundEvent.h"

#include<SDL2/SDL.h>
#include<fmod_studio.hpp>
#include<fmod_errors.h>
#include <string>

std::uint32_t AudioSystem::sNextID = 0;

AudioSystem::AudioSystem(Game* game) : 
	mGame(game),
	mSystem(nullptr), mLowLevelSystem(nullptr)
{
}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::Initialize()
{
	FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_TTY);
	FMOD_RESULT result = FMOD::Studio::System::create(&mSystem);
	if (result != FMOD_OK) {
		SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}
	result = mSystem->initialize(
		512, // Number of concurrent sound
		FMOD_STUDIO_INIT_NORMAL, // FMOD system behavior
		FMOD_INIT_NORMAL, // FMOD lowlevel system behavior
		nullptr // Extra driver data
	);
	if (result != FMOD_OK) {
		SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}
	mSystem->getLowLevelSystem(&mLowLevelSystem);
	
	// Load master bank (string first)
	this->LoadBank("Assets/Chapter7/Master Bank.strings.bank");
	this->LoadBank("Assets/Chapter7/Master Bank.bank");
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
	std::uint32_t returnID = 0;

	auto eventIter = mEvents.find(name);
	if (eventIter != mEvents.end()) {
		FMOD::Studio::EventDescription* eventDescription = eventIter->second;
		FMOD::Studio::EventInstance* eventInstance = nullptr;
		eventDescription->createInstance(&eventInstance);
		if (eventInstance) {
			eventInstance->start();

			AudioSystem::sNextID++;
			returnID = AudioSystem::sNextID;

			mEventInstances.emplace(returnID, eventInstance);
		}
	}

	return SoundEvent(this, returnID);
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(const std::uint32_t& id) const
{
	const auto& iter = mEventInstances.find(id);
	if (iter != mEventInstances.end()) {
		return iter->second;
	}

	SDL_Log("Failed to get Event Instance with ID: %s. nullptr is returned", std::to_string(id).c_str());
	return nullptr;
}

void AudioSystem::Shutdown()
{
	mSystem->release();
}

void AudioSystem::Update(float deltaTime)
{
	this->ReleaseEventInstances();
	mSystem->update();
}

void AudioSystem::LoadBank(const std::string& name)
{
	if (mBanks.find(name) != mBanks.end()) {
		return;
	}

	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = mSystem->loadBankFile(name.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
	if (result != FMOD_OK) {
		SDL_Log("Failed to load bank file: %s", name.c_str());
		return;
	}
	
	mBanks.emplace(name, bank);
	// Load all non-streaming sample data
	bank->loadSampleData();
	// Number of events in the bank
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0) {
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);
		const int maxPathLength = 512;
		char eventName[maxPathLength];
		for (std::uint16_t i = 0; i < numEvents; i++) {
			FMOD::Studio::EventDescription* eventDescription = events[i];
			eventDescription->getPath(eventName, maxPathLength, nullptr);
			mEvents.emplace(eventName, eventDescription);
		}
	}
}

void AudioSystem::UnloadBank(const std::string& name)
{
	auto bankIter = mBanks.find(name);
	if (bankIter == mBanks.end()) {
		return;
	}

	FMOD::Studio::Bank* bank = bankIter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0) {
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);
		const int maxPathLength = 512;
		char eventName[maxPathLength];
		for (std::uint16_t i = 0; i < numEvents; i++) {
			events[i]->getPath(eventName, maxPathLength, nullptr);
			auto eventIter = mEvents.find(eventName);
			if (eventIter != mEvents.end()) {
				eventIter->second->unloadSampleData();
				mEvents.erase(eventIter);
			}
		}
	}

	bank->unloadSampleData();
	bank->unload();
	mBanks.erase(bankIter);
}

void AudioSystem::UnloadAllBanks()
{
	for (const std::pair<std::string, FMOD::Studio::Bank*>& pair : mBanks) {
		pair.second->unloadSampleData();
		pair.second->unload();
	}
	mBanks.clear();
	mEvents.clear();
}

void AudioSystem::ReleaseEventInstances()
{
	std::vector<std::uint32_t> doneEventInstances;
	// Get done event instances
	for (auto& iter : mEventInstances) {
		FMOD_STUDIO_PLAYBACK_STATE state;
		iter.second->getPlaybackState(&state);
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
			iter.second->release();
			doneEventInstances.emplace_back(iter.first);
		}
	}
	// Release done event instances
	for (auto& iter : doneEventInstances) {
		mEventInstances.erase(iter);
	}
}
