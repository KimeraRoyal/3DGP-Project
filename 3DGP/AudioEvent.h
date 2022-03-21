#pragma once

#include <string>

#include <FMOD/fmod_studio.hpp>

class AudioEvent
{
private:
	FMOD::Studio::EventDescription* m_description;
	FMOD::Studio::EventInstance* m_instance;
	
	bool m_loaded;
public:
	AudioEvent(FMOD::Studio::EventDescription* _description);
	~AudioEvent();

	void Play();
	void Stop() const;

	void LoadData();
	void UnloadData();

	void CreateInstance();
	void DestroyInstance() const;

	[[nodiscard]] float GetParameterCurrentValue(const std::string& _parameterName);
	[[nodiscard]] float GetParameterFinalValue(const std::string& _parameterName);
	
	void SetParameterValue(const std::string& _parameterName, float _value, bool _instant = false);
};

