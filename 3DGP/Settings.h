#pragma once

#include <glm/vec2.hpp>

class Settings
{
private:
	glm::ivec2 m_screenResolution;
	int m_screenScale;

	float m_physicsTimestep;
public:
	glm::ivec2 GetScreenResolution() const { return m_screenResolution; }
	glm::ivec2 GetScaledScreenResolution() const { return m_screenResolution * m_screenScale; }
	int GetScreenScale() const { return m_screenScale; }

	float GetPhysicsTimestep() const { return m_physicsTimestep; }

	void SetScreenResolution(const glm::ivec2 _resolution) { m_screenResolution = _resolution; }
	void SetScreenScale(const int _scale) { m_screenScale = _scale; }

	void SetPhysicsTimestep(const float _timestep) { m_physicsTimestep = _timestep; }
};

