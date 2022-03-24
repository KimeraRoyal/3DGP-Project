#pragma once

#include "IComponent.h"

class LightComponent : public IComponent
{
private:
	glm::vec3 m_lightColor;
	float m_lightStrength;
public:
	LightComponent();

	void Start() override;
	void Update(const std::shared_ptr<Time>& _time) override;

	[[nodiscard]] glm::vec3 GetLightColor() const { return m_lightColor; }
	[[nodiscard]] float GetLightStrength() const { return m_lightStrength; }

	void SetLightColor(const glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	void SetLightStrength(const float _lightStrength) { m_lightStrength = _lightStrength; }
};
