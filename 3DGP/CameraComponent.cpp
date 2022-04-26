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
	GetGameObject()->GetScene()->FindComponents<IRenderable>(m_renderables);
}

void CameraComponent::PreDraw()
{
	const glm::mat4 projection = glm::perspective(glm::radians(m_fov), static_cast<float>(Window::GetWindowSize().x) / static_cast<float>(Window::GetWindowSize().y), m_nearPlane, m_farPlane);

	Clear();
	
	for(const std::shared_ptr<IRenderable>& renderable : m_renderables)
	{
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

std::shared_ptr<IComponent> CameraComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<CameraComponent> component = std::make_unique<CameraComponent>();
	
	component->SetClearColor(ParseVector(_value["clearColor"]));
	
	component->SetFOV(_value["fov"].GetFloat());

	component->SetNearPlane(_value["near"].GetFloat());
	component->SetFarPlane(_value["far"].GetFloat());
	
	return std::static_pointer_cast<IComponent>(component);
}
