#pragma once

#include <rapidjson/document.h>

#include "IComponent.h"
#include "IJsonParser.h"
#include "ShaderProgram.h"

class ILight;

class LightComponent : public IComponent
{
private:
	std::shared_ptr<ILight> m_light;
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};
	
	LightComponent();

	void Start() override;

	std::shared_ptr<IComponent> GenerateClone() override;

	void AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const;

	[[nodiscard]] std::shared_ptr<ILight> GetLight() const { return m_light; }
	
	void SetLight(const std::shared_ptr<ILight>& _light) { m_light = _light; }
};
