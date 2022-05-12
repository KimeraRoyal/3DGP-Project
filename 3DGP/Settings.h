#pragma once

#include <glm/vec2.hpp>

class Settings
{
private:
	friend class SettingsParser;
	
	glm::uvec2 m_screenResolution;
	unsigned int m_screenScale;

	unsigned int m_multisample;

	float m_physicsTimestep;

	void SetScreenResolution(const glm::uvec2 _resolution) { m_screenResolution = _resolution; }
	void SetScreenScale(const unsigned int _scale) { m_screenScale = _scale; }

	void SetMultisampleCount(const unsigned int _multisample) { m_multisample = _multisample; }

	void SetPhysicsTimestep(const float _timestep) { m_physicsTimestep = _timestep; }
public:
	Settings() : m_screenResolution(glm::uvec2(1)), m_screenScale(1), m_multisample(1), m_physicsTimestep(0.1f) {}
	
	[[nodiscard]] glm::uvec2 GetScreenResolution() const { return m_screenResolution; }
	[[nodiscard]] glm::uvec2 GetScaledScreenResolution() const { return m_screenResolution * m_screenScale; }
	[[nodiscard]] unsigned int GetScreenScale() const { return m_screenScale; }
	
	[[nodiscard]] unsigned int GetMultisampleCount() const { return m_multisample; }
	[[nodiscard]] bool GetMultisamplingEnabled() const { return m_multisample > 0; }

	[[nodiscard]] float GetPhysicsTimestep() const { return m_physicsTimestep; }
};

