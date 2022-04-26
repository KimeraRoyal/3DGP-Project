#include "Audio.h"

#include <FMOD/fmod_errors.h>

#include "AudioEvent.h"
#include "File.h"

Audio::Audio()
{
	m_fmodSystem = nullptr;
	
	ErrorCheck(FMOD::Studio::System::create(&m_fmodSystem));
	ErrorCheck(m_fmodSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr));
}

Audio::~Audio()
{
	for(FMOD::Studio::Bank* bank : m_banks)
	{
		bank->unload();
	}
	m_fmodSystem->release();
}

void Audio::Update() const
{
	m_fmodSystem->update();
}

void Audio::LoadBank(const std::string& _fileName)
{
	const std::string path = File::GetBasePath() + _fileName;

	FMOD::Studio::Bank* bank;
	ErrorCheck(m_fmodSystem->loadBankFile(path.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));

	m_banks.push_back(bank);
}

std::shared_ptr<AudioEvent> Audio::CreateAudioEvent(const std::string& _path) const
{
	FMOD::Studio::EventDescription* eventDescription = GetEventDescription(_path);
	std::shared_ptr<AudioEvent> audioEvent = std::make_unique<AudioEvent>(eventDescription);

	return audioEvent;
}

void Audio::PlayOneShot(const std::string& _path) const
{
	FMOD::Studio::EventDescription* eventDescription = GetEventDescription(_path);
	
	FMOD::Studio::EventInstance* eventInstance;
	ErrorCheck(eventDescription->createInstance(&eventInstance));
	
	ErrorCheck(eventInstance->start());
	ErrorCheck(eventInstance->release());
}

FMOD::Studio::EventDescription* Audio::GetEventDescription(const std::string& _path) const
{
	FMOD::Studio::EventDescription* eventDescription;
	ErrorCheck(m_fmodSystem->getEvent(_path.c_str(), &eventDescription));

	return eventDescription;
}

void Audio::ErrorCheck(const FMOD_RESULT _result)
{
	if (_result != FMOD_OK)
	{
		printf("FMOD Encountered an Error: (%d) %s\n", _result, FMOD_ErrorString(_result));
		throw std::exception();
	}
}