#include "RenderingSystem.h"

#include "Window.h"
#include "Quad.h"
#include "CameraComponent.h"

size_t RenderingSystem::s_projectionKey = std::hash<std::string>()("in_Projection");
size_t RenderingSystem::s_modelKey = std::hash<std::string>()("in_Model");
size_t RenderingSystem::s_viewPosKey = std::hash<std::string>()("in_ViewPos");

RenderingSystem::RenderingSystem(Resources* _resources)
{
	m_gBuffer = std::make_unique<RenderTexture>(Window::GetScaledWindowSize().x, Window::GetScaledWindowSize().y);
	m_gBuffer->AddColorBuffers(2, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_gBuffer->AddColorBuffer(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_gBuffer->SetRenderbuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
	
	m_quad = std::make_unique<Quad>(m_gBuffer);
	
	m_program = _resources->GetProgram("data/shaders/screen/screen.vert", "data/shaders/deferred/lightingPass.frag");
}


void RenderingSystem::Start(const std::shared_ptr<Scene>& _scene)
{
	m_camera = _scene->FindComponent<CameraComponent>();
}

void RenderingSystem::Draw() const
{
	const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Window::GetWindowSize().x), 0.0f, static_cast<float>(Window::GetWindowSize().y), 0.0f, 1.0f);

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(Window::GetWindowSize(), 0) / 2.0f);
	model = glm::scale(model, glm::vec3(Window::GetWindowSize(), 1));
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind color buffers and program.
	glUseProgram(m_program->GetId());
	m_gBuffer->BindAll();

	// Set the uniforms to draw.
	m_program->SetUniformValueByKey(s_projectionKey, projection);
	m_program->SetUniformValueByKey(s_modelKey, model);
	
	m_program->SetUniformValue(s_viewPosKey, m_camera->GetViewMatrix());

	// Draw to the quad.
	m_quad->Draw();

	// Unbind color buffers and program.
	m_gBuffer->UnbindAll();
	glUseProgram(0);
}
