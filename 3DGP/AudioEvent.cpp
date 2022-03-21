#include "AudioEvent.h"

#include <stdexcept>
#include <memory>

#include "Audio.h"

AudioEvent::AudioEvent(FMOD::Studio::EventDescription* _description)
{
	m_description = _description;
	m_instance = nullptr;

	m_loaded = false;
}

AudioEvent::~AudioEvent()
{
	if(m_instance)
	{
		m_instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
		m_instance->release();
	}

	if(m_loaded)
	{
		m_description->unloadSampleData();
	}
}

void AudioEvent::Play()
{
	if (!m_instance) { CreateInstance(); }
	
	Audio::ErrorCheck(m_instance->start());
}

void AudioEvent::Stop() const
{
	if (!m_instance) { return; }
	
	Audio::ErrorCheck(m_instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
}

void AudioEvent::LoadData()
{
	if (m_loaded) { return; }
	
	Audio::ErrorCheck(m_description->loadSampleData());
	m_loaded = true;
}

void AudioEvent::UnloadData()
{
	if (!m_loaded) { return; }
	
	Audio::ErrorCheck(m_description->unloadSampleData());
	m_loaded = false;
}

void AudioEvent::CreateInstance()
{
	if (m_instance) { return; }
	
	Audio::ErrorCheck(m_description->createInstance(&m_instance));
}

void AudioEvent::DestroyInstance() const
{
	if (!m_instance) { return; }
	
	Stop();
	Audio::ErrorCheck(m_instance->release());
}

float AudioEvent::GetParameterCurrentValue(const std::string& _parameterName)
{
	if (!m_instance) { CreateInstance(); }

	float value;
	Audio::ErrorCheck(m_instance->getParameterByName(_parameterName.c_str(), &value, nullptr));
	return value;
}

float AudioEvent::GetParameterFinalValue(const std::string& _parameterName)
{
	if (!m_instance) { CreateInstance(); }

	float value;
	Audio::ErrorCheck(m_instance->getParameterByName(_parameterName.c_str(), nullptr, &value));
	return value;
}

void AudioEvent::SetParameterValue(const std::string& _parameterName, const float _value, const bool _instant)
{
	if (!m_instance) { CreateInstance(); }
	
	Audio::ErrorCheck(m_instance->setParameterByName(_parameterName.c_str(), _value, _instant));
}
