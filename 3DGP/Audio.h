#pragma once

#include <string>
#include <vector>
#include <memory>

#include <FMOD/fmod_studio.hpp>

class AudioEvent;

class Audio
{
private:
	FMOD::Studio::System* m_fmodSystem;

	std::vector<FMOD::Studio::Bank*> m_banks;

	[[nodiscard]] FMOD::Studio::EventDescription* GetEventDescription(const std::string& _path) const;
public:
	Audio();
	~Audio();

	void Update() const;

	void LoadBank(const std::string& _fileName);

	[[nodiscard]] std::shared_ptr<AudioEvent> CreateAudioEvent(const std::string& _path) const;
	void PlayOneShot(const std::string& _path) const;

	static void ErrorCheck(FMOD_RESULT _result);
};

