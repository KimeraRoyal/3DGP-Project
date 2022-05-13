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
	bool m_enableVsync;

	float m_physicsTimestep;

	void SetControlWindowMovement(const bool _controlMovement) { m_controlWindowMovement = _controlMovement; }
	void SetWindowAnchor(const glm::vec2 _anchor) { m_windowAnchor = _anchor; }
	void SetWindowPosition(const glm::vec2 _position) { m_windowPosition = _position; }

	void SetWindowResolution(const glm::uvec2 _resolution) { m_windowResolution = _resolution; }
	void SetWindowScale(const unsigned int _scale) { m_windowScale = _scale; }
	void SetEnableVsync(const bool _enableVsync) { m_enableVsync = _enableVsync; }

	void SetPhysicsTimestep(const float _timestep) { m_physicsTimestep = _timestep; }
public:
	Settings()
	: m_controlWindowMovement(false), m_windowAnchor(0.5f), m_windowPosition(0.0f),
		m_windowResolution(glm::uvec2(1)), m_windowScale(1), m_enableVsync(true),
		m_physicsTimestep(0.1f) {}

	[[nodiscard]] bool GetControlWindowMovement() const { return m_controlWindowMovement; }
	[[nodiscard]] glm::vec2 GetWindowAnchor() const { return m_windowAnchor; }
	[[nodiscard]] glm::vec2 GetWindowPosition() const { return m_windowPosition; }
	
	[[nodiscard]] glm::uvec2 GetWindowResolution() const { return m_windowResolution; }
	[[nodiscard]] glm::uvec2 GetScaledWindowResolution() const { return m_windowResolution * m_windowScale; }
	[[nodiscard]] unsigned int GetWindowScale() const { return m_windowScale; }
	[[nodiscard]] bool GetEnableVsync() const { return m_enableVsync; }

	[[nodiscard]] float GetPhysicsTimestep() const { return m_physicsTimestep; }
};

