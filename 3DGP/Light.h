#pragma once

#include "Transform.h"

class Light
{
private:
	Transform m_transform;

	glm::vec3 m_lightColor;
	float m_lightStrength;
public:
	Light();

	Transform* GetTransform() { return &m_transform; }

	[[nodiscard]] glm::vec3 GetLightColor() const { return m_lightColor; }
	[[nodiscard]] float GetLightStrength() const { return m_lightStrength; }

	void SetLightColor(const glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	void SetLightStrength(const float _lightStrength) { m_lightStrength = _lightStrength; }
};
