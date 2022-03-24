#include "LightComponent.h"

LightComponent::LightComponent()
{
	m_lightColor = glm::vec3(1.0f);
	m_lightStrength = 1.0f;
}

void LightComponent::Start()
{
	GetGameObject()->GetTransform()->SetPosition(glm::vec3(-10.0f, 5.0f, -8.0f));
}

void LightComponent::Update(const std::shared_ptr<Time>& _time)
{
	GetGameObject()->GetTransform()->SetPosition(glm::vec3(10.0f * cos(_time->GetTime()), 10.0f * sin(_time->GetTime()), 0.0f));
}