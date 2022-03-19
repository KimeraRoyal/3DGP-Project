#pragma once

#include <SDL2/SDL.h>

class Time
{
private:
	Uint64 m_lastCounterValue = 0;

	float m_deltaTime = 0;
	float m_time = 0;
public:
	Time() = default;
	
	Time(const Time& _copy) = delete;
	Time& operator=(const Time& _other) = delete;
	
	void Update();

	[[nodiscard]] float GetDeltaTime() const;
	[[nodiscard]] float GetTime() const;
};