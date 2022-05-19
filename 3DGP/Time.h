#pragma once

#include <SDL2/SDL.h>

class Time
{
private:
	Uint64 m_lastCounterValue = 0;

	float m_deltaTime = 0;
	float m_time = 0;

	int m_frames = 0;
	int m_fps = 60;

	float m_fpsTimer = 0;
	int m_framesInSecond = 0;

	void CalculateTime();
	void CalculateFPS();
public:
	Time() = default;
	
	Time(const Time& _copy) = delete;
	Time& operator=(const Time& _other) = delete;
	
	void Update();

	[[nodiscard]] float GetDeltaTime() const { return m_deltaTime; }
	[[nodiscard]] float GetTime() const { return m_time; }

	[[nodiscard]] int GetFrames() const { return m_frames; }
	[[nodiscard]] int GetFPS() const { return m_fps; }
};