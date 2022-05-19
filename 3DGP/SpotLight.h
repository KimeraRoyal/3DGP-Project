#pragma once

#include <glm/trigonometric.hpp>

#include "ILight.h"

class SpotLight : public ILight
{
	static size_t s_positionKey;
	static size_t s_directionKey;

	static size_t s_ambientKey;
	static size_t s_diffuseKey;
	static size_t s_specularKey;

	static size_t s_innerKey;
	static size_t s_outerKey;

	float m_innerCutoff;
	float m_outerCutoff;
public:
	SpotLight() : ILight(), m_innerCutoff(0.0f), m_outerCutoff(0.0f) {}
	~SpotLight() override = default;

	std::shared_ptr<ILight> GenerateClone() override;

	void AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) override;

	void SetInnerCutoff(const float _angle) { m_innerCutoff = glm::cos(glm::radians(_angle)); }
	void SetOuterCutoff(const float _angle) { m_outerCutoff = glm::cos(glm::radians(_angle)); }
};
