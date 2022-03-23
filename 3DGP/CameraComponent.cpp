#include "CameraComponent.h"

#include <GL/glew.h>

CameraComponent::CameraComponent()
{
	m_clearColor = glm::vec3(0.0f);
}

void CameraComponent::Start()
{
	SetClearColor(glm::vec3(0.65f, 0.5f, 0.9f));
}

void CameraComponent::Update(const std::shared_ptr<Time>& _time)
{
	GetGameObject()->GetTransform()->SetPosition(glm::vec3(6.0f, 0.0f, 0.0f) * cos(_time->GetTime() / 2.0f));
	GetGameObject()->GetTransform()->SetRotation(glm::vec3(0.0, 30.0f, 0.0f) * cos(_time->GetTime() / 2.0f));
}

void CameraComponent::Clear() const
{
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
