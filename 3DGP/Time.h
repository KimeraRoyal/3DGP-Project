#pragma once

#include <SDL2/SDL.h>

class Time
{
private:
	Uint64 m_lastCounterValue = 0;

	float m_deltaTime = 0;
public:
	void Update();

	float GetDeltaTime() const;
};