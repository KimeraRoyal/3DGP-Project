#include "CameraComponent.h"

#include <GL/glew.h>

#include "Scene.h"
#include "Window.h"

size_t CameraComponent::s_viewKey = std::hash<std::string>()("in_View");
size_t CameraComponent::s_projectionKey = std::hash<std::string>()("in_Projection");
size_t CameraComponent::s_viewPosKey = std::hash<std::string>()("in_ViewPos");

CameraComponent::CameraComponent()
{
	m_clearColor = glm::vec3(0.0f);

	m_fov = 45.0f;

	m_nearPlane = 0.1f;
	m_farPlane = 100.0f;
}

void CameraComponent::Start()
{
	GetScene()->GetRenderingSystem()->AddCamera(std::dynamic_pointer_cast<CameraComponent>(shared_from_this()));
}

std::shared_ptr<IComponent> CameraComponent::GenerateClone()
{
	const std::shared_ptr<CameraComponent> component = std::make_shared<CameraComponent>();
	component->m_clearColor = m_clearColor;
	component->m_fov = m_fov;
	component->m_nearPlane = m_nearPlane;
	component->m_farPlane = m_farPlane;
	return component;
}

void CameraComponent::DrawRenderables(const std::vector<std::shared_ptr<RenderableComponent>>& _renderables) const
{
	const glm::mat4 projection = glm::perspective(glm::radians(m_fov), static_cast<float>(Window::GetInstance()->GetResolution().x) / static_cast<float>(Window::GetInstance()->GetResolution().y), m_nearPlane, m_farPlane);

	Clear();
	
	for(const std::shared_ptr<RenderableComponent>& renderable : _renderables)
	{
		if (!renderable->GetActive()) { continue; }
		
		// Bind shader program
		glUseProgram(renderable->GetProgram()->GetId());

		// Set uniform values
		renderable->GetProgram()->SetUniformValueByKey(s_viewKey, GetViewMatrix());
		renderable->GetProgram()->SetUniformValueByKey(s_projectionKey, projection);

		renderable->GetProgram()->SetUniformValueByKey(s_viewPosKey, GetTransform()->GetPosition());

		// Draw
		renderable->Draw();

		// Unbind shader program
		glUseProgram(0);
	}
}


void CameraComponent::Clear() const
{
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::mat4 CameraComponent::GetViewMatrix() const
{
	return glm::inverse(GetGameObject()->GetTransform()->GetModelMatrix());
}

std::shared_ptr<IComponent> CameraComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<CameraComponent> component = std::make_unique<CameraComponent>();
	
	component->SetClearColor(ParseVector3(_value["clearColor"]));
	
	component->SetFOV(_value["fov"].GetFloat());

	component->SetNearPlane(_value["near"].GetFloat());
	component->SetFarPlane(_value["far"].GetFloat());
	
	return std::static_pointer_cast<IComponent>(component);
}
