#pragma once

#include <glm/vec2.hpp>

class Settings
{
private:
	friend class SettingsParser;

	bool m_controlWindowMovement;
	glm::vec2 m_windowAnchor;
	glm::vec2 m_windowPosition;
	
	glm::uvec2 m_windowResolution;
	unsigned int m_windowScale;

	unsigned int m_multisample;

	float m_physicsTimestep;

	void SetControlWindowMovement(const bool _controlMovement) { m_controlWindowMovement = _controlMovement; }
	void SetWindowAnchor(const glm::vec2 _anchor) { m_windowAnchor = _anchor; }
	void SetWindowPosition(const glm::vec2 _position) { m_windowPosition = _position; }

	void SetWindowResolution(const glm::uvec2 _resolution) { m_windowResolution = _resolution; }
	void SetWindowScale(const unsigned int _scale) { m_windowScale = _scale; }

	void SetMultisampleCount(const unsigned int _multisample) { m_multisample = _multisample; }

	void SetPhysicsTimestep(const float _timestep) { m_physicsTimestep = _timestep; }
public:
	Settings()
	: m_controlWindowMovement(false), m_windowAnchor(0.5f), m_windowPosition(0.0f),
		m_windowResolution(glm::uvec2(1)), m_windowScale(1), m_multisample(1),
		m_physicsTimestep(0.1f) {}

	[[nodiscard]] bool GetControlWindowMovement() const { return m_controlWindowMovement; }
	[[nodiscard]] glm::vec2 GetWindowAnchor() const { return m_windowAnchor; }
	[[nodiscard]] glm::vec2 GetWindowPosition() const { return m_windowPosition; }
	
	[[nodiscard]] glm::uvec2 GetWindowResolution() const { return m_windowResolution; }
	[[nodiscard]] glm::uvec2 GetScaledWindowResolution() const { return m_windowResolution * m_windowScale; }
	[[nodiscard]] unsigned int GetWindowScale() const { return m_windowScale; }
	
	[[nodiscard]] unsigned int GetMultisampleCount() const { return m_multisample; }
	[[nodiscard]] bool GetMultisamplingEnabled() const { return m_multisample > 0; }

	[[nodiscard]] float GetPhysicsTimestep() const { return m_physicsTimestep; }
};

