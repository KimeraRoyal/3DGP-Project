#include "Time.h"

void Time::Update()
{
	m_frames++;

	CalculateTime();
	CalculateFPS();
}

void Time::CalculateTime()
{
	const Uint64 currentCounterValue = SDL_GetPerformanceCounter();

	if (m_lastCounterValue)
	{
		m_deltaTime = static_cast<float>((currentCounterValue - m_lastCounterValue) * 1000) / static_cast<float>(SDL_GetPerformanceFrequency()) * 0.001f;
	}
	m_time += m_deltaTime;

	m_lastCounterValue = currentCounterValue;
}

void Time::CalculateFPS()
{
	m_fpsTimer += m_deltaTime;
	m_framesInSecond++;

	if (m_fpsTimer >= 1.0f)
	{
		m_fps = m_framesInSecond;
		m_framesInSecond = 0;

		m_fpsTimer -= 1.0f;
	}
}