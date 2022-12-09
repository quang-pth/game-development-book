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
		FMOD_INIT_CHANNEL_LOWPASS, // Enable low-pass filtering (Occlusion)
		nullptr // Extra driver data
	);
	if (result != FMOD_OK) {
		SDL_Log("Failed to initialize FMOD System: %s", FMOD_ErrorString(result));
		return false;
	}
	result = mSystem->getLowLevelSystem(&mLowLevelSystem);
	if (result != FMOD_OK) {
		SDL_Log("Failed to initialize FMOD Low Level System: %s", FMOD_ErrorString(result));
		return false;
	}
	mLowLevelSystem->set3DSettings(
		10.0f, // Doppler scale
		50.0f, // Game units (1 unit = 1 meter)
		1.0f // Not for Doppler, let it be 1
	);

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
			// Play sound event
			eventInstance->start();

			AudioSystem::sNextID++;
			returnID = AudioSystem::sNextID;

			mEventInstances.emplace(returnID, eventInstance);
		}
	}

	return SoundEvent(this, returnID);
}

float AudioSystem::GetBusVolume(const std::string& name) const
{
	float volume = 0.0f;
	const auto& iter = mBuses.find(name);
	if (iter != mBuses.end()) {
		iter->second->getVolume(&volume);
	}
	return volume;
}

bool AudioSystem::GetBusPaused(const std::string& name) const
{
	bool paused = false;
	const auto& iter = mBuses.find(name);
	if (iter != mBuses.end()) {
		iter->second->getPaused(&paused);
	}
	return paused;
}

void AudioSystem::SetBusVolume(const std::string& name, float value)
{
	const auto& iter = mBuses.find(name);
	if (iter != mBuses.end()) {
		iter->second->setVolume(value);
	}
}

void AudioSystem::SetBusPause(const std::string& name, bool pause)
{
	const auto& iter = mBuses.find(name);
	if (iter != mBuses.end()) {
		iter->second->setPaused(pause);
	}
}

void AudioSystem::SetListener(const Matrix4& viewMatrix, const Vector3& offset)
{
	Matrix4 invertMatrix = viewMatrix;
	invertMatrix.Invert();

	// Setup listener by its World Position and World Orientation
	FMOD_3D_ATTRIBUTES listener;
	listener.position = VecToFMOD(invertMatrix.GetTranslation() - offset);
	listener.forward = VecToFMOD(invertMatrix.GetZAxis());
	listener.up = VecToFMOD(invertMatrix.GetYAxis());
	listener.velocity = { 240.0f };
	// Send listener to FMOD
	mSystem->setListenerAttributes(
		0, // Only 1 listener
		&listener // Listener attributes
	);
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(const std::uint32_t& id) const
{
	auto iter = mEventInstances.find(id);
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
	// ================================ EVENT DESCRIPTIONS ===================
	bank->loadSampleData();
	// Number of events in the bank
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0) {
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);
		const int maxPathLength = 512;
		char eventName[maxPathLength];
		for (int i = 0; i < numEvents; i++) {
			FMOD::Studio::EventDescription* eventDescription = events[i];
			eventDescription->getPath(eventName, maxPathLength, nullptr);
			mEvents.emplace(eventName, eventDescription);
		}
	}
	// ================================ END EVENT DESCRIPTIONS ===================
	// ===================================================================== 
	// ================================ BUSES ======================= 
	int busCount = 0;
	bank->getBusCount(&busCount);
	if (busCount > 0) {
		std::vector<FMOD::Studio::Bus*> buses(busCount);
		bank->getBusList(buses.data(), busCount, &busCount);
		const int maxPathLength = 512;
		char busName[512];
		for (int i = 0; i < busCount; i++) {
			FMOD::Studio::Bus* bus = buses[i];
			bus->getPath(busName, maxPathLength, nullptr);
			mBuses.emplace(busName, bus);
		}
	}
	// ================================ END BUSES ===================
}

void AudioSystem::UnloadBank(const std::string& name)
{
	auto bankIter = mBanks.find(name);
	if (bankIter == mBanks.end()) {
		return;
	}

	FMOD::Studio::Bank* bank = bankIter->second;
	// ================= UNLOAD EVENT DESCRIPTIONS =========================
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0) {
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);
		const int maxPathLength = 512;
		char eventName[maxPathLength];
		for (int i = 0; i < numEvents; i++) {
			events[i]->getPath(eventName, maxPathLength, nullptr);
			const auto& eventIter = mEvents.find(eventName);
			if (eventIter != mEvents.end()) {
				eventIter->second->unloadSampleData();
				mEvents.erase(eventIter);
			}
		}
	}
	// ================= END UNLOAD EVENT DESCRIPTIONS =========================
	// ================= UNLOAD BUSES =========================
	int busCount = 0;
	bank->getBusCount(&busCount);
	if (busCount > 0) {
		std::vector<FMOD::Studio::Bus*> buses(busCount);
		bank->getBusList(buses.data(), busCount, &busCount);
		const int maxPathLength = 512;
		char busName[512];
		for (int i = 0; i < busCount; i++) {
			buses[i]->getPath(busName, maxPathLength, nullptr);
			const auto& busIter = mBuses.find(busName);
			if (busIter != mBuses.end()) {
				busIter->second->stopAllEvents(FMOD_STUDIO_STOP_ALLOWFADEOUT);
				mBuses.erase(busIter->first);
			}
		}
	}
	// ================= END UNLOAD BUSES =========================

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
	mBuses.clear();
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

// Convert vector from (x+ forward, y+ right, z+ up) coords
// to FMOD coords (x+ right, y+ up, z+ forward)
FMOD_VECTOR VecToFMOD(const Vector3& vector)
{
	FMOD_VECTOR vect;
	vect.x = vector.y;
	vect.y = vector.z;
	vect.z = vector.x;
	return vect;
}
