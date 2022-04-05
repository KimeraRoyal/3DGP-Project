#include "CameraComponent.h"

#include <GL/glew.h>

#include "Scene.h"
#include "Window.h"

CameraComponent::CameraComponent()
{
	m_clearColor = glm::vec3(0.0f);

	m_fov = 45.0f;

	m_nearPlane = 0.1f;
	m_farPlane = 100.0f;
}

void CameraComponent::Start()
{
	SetClearColor(glm::vec3(0.65f, 0.5f, 0.9f));

	GetGameObject()->GetScene()->FindComponents<IRenderable>(m_renderables);
}

void CameraComponent::Update(const std::shared_ptr<Time>& _time)
{
	GetGameObject()->GetTransform()->SetPosition(glm::vec3(6.0f, 0.0f, 0.0f) * cos(_time->GetTime() / 2.0f));
	GetGameObject()->GetTransform()->SetRotation(glm::vec3(0.0, 30.0f, 0.0f) * cos(_time->GetTime() / 2.0f));
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
		renderable->GetProgram()->SetUniformValue("in_View", GetViewMatrix());
		renderable->GetProgram()->SetUniformValue("in_Projection", projection);

		renderable->GetProgram()->SetUniformValue("in_ViewPos", GetTransform()->GetPosition());

		//TODO: Generate hashtable within ShaderProgram that returns and stores uniform ids. O(1) lookup babey!!

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
