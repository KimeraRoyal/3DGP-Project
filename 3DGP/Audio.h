#pragma once

#include <string>
#include <vector>

#include <FMOD/fmod_studio.hpp>

class Audio
{
private:
	FMOD::Studio::System* m_fmodSystem;

	std::vector<FMOD::Studio::Bank*> m_banks;

	static void ErrorCheck(FMOD_RESULT _result);
public:
	Audio();
	~Audio();

	void Update() const;

	void LoadBank(const std::string& _fileName);

	[[nodiscard]] FMOD::Studio::EventDescription* GetEventDescription(const std::string& _eventName) const;
	
	[[nodiscard]] FMOD::Studio::EventInstance* CreateEventInstance(FMOD::Studio::EventDescription* _eventDescription) const;
	[[nodiscard]] FMOD::Studio::EventInstance* CreateEventInstance(const std::string& _eventName) const;
	
	void PlayOneShot(const std::string& _eventName) const;
};

