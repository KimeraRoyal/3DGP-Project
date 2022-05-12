#include "Screen.h"

#include "Quad.h"
#include "Shader.h"
#include "Window.h"

size_t Screen::s_projectionKey = std::hash<std::string>()("in_Projection");
size_t Screen::s_modelKey = std::hash<std::string>()("in_Model");

Screen::Screen(const std::shared_ptr<ShaderProgram>& _shaderProgram, const unsigned int _colorBufferCount)
{
	m_renderTexture = std::make_unique<RenderTexture>(Window::GetInstance()->GetScreenResolution().x, Window::GetInstance()->GetScreenResolution().y);
	m_renderTexture->AddColorBuffers(_colorBufferCount);
	
	m_screenQuad = std::make_unique<Quad>(m_renderTexture);

	// Create program
	m_program = _shaderProgram;
}

void Screen::Draw() const
{
	const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Window::GetInstance()->GetResolution().x), 0.0f, static_cast<float>(Window::GetInstance()->GetResolution().y), 0.0f, 1.0f);

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(Window::GetInstance()->GetResolution(), 0) / 2.0f);
	model = glm::scale(model, glm::vec3(Window::GetInstance()->GetResolution(), 1));

	glUseProgram(m_program->GetId());

	m_program->SetUniformValueByKey(s_projectionKey, projection);
	m_program->SetUniformValueByKey(s_modelKey, model);

	m_screenQuad->Draw();

	glUseProgram(0);
}
