#include "LightComponent.h"

#include "Scene.h"

#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

LightComponent::LightComponent()
{
	m_light = nullptr;
}

void LightComponent::Start()
{
	m_light->SetTransform(GetTransform());

	GetScene()->GetRenderingSystem()->AddLight(std::dynamic_pointer_cast<LightComponent>(shared_from_this()));
}

void LightComponent::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const
{
	m_light->AssignUniforms(_program);
}

std::shared_ptr<IComponent> LightComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<LightComponent> component = std::make_unique<LightComponent>();

	const std::string lightType = _value["type"].GetString();
	if (lightType == "ambient") // Ambient
	{
		component->SetLight(std::make_unique<AmbientLight>());
	}
	else if (lightType == "directional") // Directional
	{
		component->SetLight(std::make_unique<DirectionalLight>());
	}
	else if (lightType == "spotlight") // Spot
	{
		std::shared_ptr<SpotLight> spot = std::make_unique<SpotLight>();
		spot->SetInnerCutoff(_value["inner"].GetFloat());
		spot->SetOuterCutoff(_value["outer"].GetFloat());
		component->SetLight(spot);
	}
	else // Point
	{
		std::shared_ptr<PointLight> point = std::make_unique<PointLight>();
		point->SetRadius(_value["radius"].GetFloat());
		component->SetLight(point);
	}
	
	component->GetLight()->SetLightColor(ParseVector(_value["color"]));
	component->GetLight()->SetLightStrength(_value["strength"].GetFloat());
	
	return std::static_pointer_cast<IComponent>(component);
}
