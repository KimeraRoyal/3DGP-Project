#pragma once

#include "ILight.h"

class PointLight final : public ILight
{
private:
	static size_t s_positionKey;
	
	static size_t s_ambientKey;
	static size_t s_diffuseKey;
	static size_t s_specularKey;
	
	static size_t s_radiusKey;

	float m_radius;
public:
	PointLight() : ILight(), m_radius(0.0f) {}
	~PointLight() override = default;

	std::shared_ptr<ILight> GenerateClone() override;

	void AssignUniforms(const std::shared_ptr<ShaderProgram>&_program) override;

	[[nodiscard]] float GetRadius() const { return m_radius; }

	void SetRadius(const float _radius) { m_radius = _radius; }
};

