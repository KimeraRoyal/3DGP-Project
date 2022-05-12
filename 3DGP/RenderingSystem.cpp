#include "RenderingSystem.h"

#include "Window.h"
#include "Quad.h"
#include "CameraComponent.h"
#include "LightComponent.h"

size_t RenderingSystem::s_projectionKey = std::hash<std::string>()("in_Projection");
size_t RenderingSystem::s_modelKey = std::hash<std::string>()("in_Model");
size_t RenderingSystem::s_viewPosKey = std::hash<std::string>()("in_ViewPos");

RenderingSystem::RenderingSystem(Resources* _resources)
{
	m_gBuffer = std::make_unique<RenderTexture>(Window::GetInstance()->GetScreenResolution().x, Window::GetInstance()->GetScreenResolution().y);
	m_gBuffer->AddColorBuffers(2, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_gBuffer->AddColorBuffer(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_gBuffer->SetRenderbuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
	
	m_quad = std::make_unique<Quad>(m_gBuffer);
	m_quad->SetActiveTexture(4);
	
	m_program = _resources->GetProgram("data/shaders/screen/screen.vert", "data/shaders/deferred/lightingPass.frag");
}

void RenderingSystem::PreDraw()
{
	Bind();
	bool activeCameras = false;
	for(const std::shared_ptr<CameraComponent>& camera : m_cameras)
	{
		if (!camera->GetActive()) { continue; }
		camera->DrawRenderables(m_renderables);

		activeCameras = true;
	}
	if (!activeCameras) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	Unbind();
}

void RenderingSystem::Draw() const
{
	const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Window::GetInstance()->GetResolution().x), 0.0f, static_cast<float>(Window::GetInstance()->GetResolution().y), 0.0f, 1.0f);

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(Window::GetInstance()->GetResolution(), 0) / 2.0f);
	model = glm::scale(model, glm::vec3(Window::GetInstance()->GetResolution(), 1));
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind color buffers and program.
	glUseProgram(m_program->GetId());
	m_gBuffer->BindAll(m_program->GetId());

	// Set the uniforms to draw.
	m_program->SetUniformValueByKey(s_projectionKey, projection);
	m_program->SetUniformValueByKey(s_modelKey, model);

	for (const std::shared_ptr<LightComponent>& light : m_lights)
	{
		if (!light->GetActive()) { continue; }
		light->AssignUniforms(m_program);
	}

	// Draw to the quad.
	m_quad->Draw();

	// Unbind color buffers and program.
	m_gBuffer->UnbindAll();
	glUseProgram(0);
}
