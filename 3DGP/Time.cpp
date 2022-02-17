#include "Time.h"

void Time::Update()
{
	const Uint64 currentCounterValue = SDL_GetPerformanceCounter();

	if (m_lastCounterValue)
	{
		m_deltaTime = static_cast<float>((currentCounterValue - m_lastCounterValue) * 1000) / static_cast<float>(SDL_GetPerformanceFrequency()) * 0.001f;
	}

	m_lastCounterValue = currentCounterValue;
}

float Time::GetDeltaTime() const
{
	return m_deltaTime;
}