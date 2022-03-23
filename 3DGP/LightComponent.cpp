#include "LightComponent.h"

LightComponent::LightComponent()
{
	m_lightColor = glm::vec3(1.0f);
	m_lightStrength = 1.0f;
}

void LightComponent::Update(const std::shared_ptr<Time>& _time)
{
	GetGameObject()->GetTransform()->SetPosition(glm::vec3(10.0f, 0.0f, 0.0f) * sin(_time->GetTime()));
}