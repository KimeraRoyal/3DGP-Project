#pragma once

#include <rapidjson/document.h>

#include "IComponent.h"
#include "IJsonParser.h"
#include "ShaderProgram.h"

class LightComponent : public IComponent
{
private:
	static size_t s_lightPosKey;
	static size_t s_ambientKey;
	static size_t s_diffuseKey;
	static size_t s_specularKey;
	
	glm::vec3 m_lightColor;
	float m_lightStrength;
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};
	
	LightComponent();

	void Start() override;

	void AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const;

	[[nodiscard]] glm::vec3 GetLightColor() const { return m_lightColor; }
	[[nodiscard]] float GetLightStrength() const { return m_lightStrength; }

	void SetLightColor(const glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	void SetLightStrength(const float _lightStrength) { m_lightStrength = _lightStrength; }
};
