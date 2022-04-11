#include "LightComponent.h"

size_t LightComponent::s_lightPosKey = std::hash<std::string>()("in_LightPos");

LightComponent::LightComponent()
{
	m_lightColor = glm::vec3(1.0f);
	m_lightStrength = 1.0f;
}

void LightComponent::Start()
{
	GetGameObject()->GetTransform()->SetPosition(glm::vec3(-10.0f, 5.0f, -8.0f));
}

void LightComponent::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const
{
	_program->SetUniformValueByKey(s_lightPosKey, GetTransform()->GetPosition());
}

std::shared_ptr<IComponent> LightComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<LightComponent> component = std::make_unique<LightComponent>();

	component->SetLightColor(ParseVector(_value["color"]));
	component->SetLightStrength(_value["strength"].GetFloat());
	
	return std::static_pointer_cast<IComponent>(component);
}
