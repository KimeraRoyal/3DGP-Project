#include "Screen.h"

#include <glm/gtc/type_ptr.hpp>

#include "Quad.h"
#include "Shader.h"
#include "Window.h"

Screen::Screen(const std::string& _vertShader, const std::string& _fragShader, const unsigned int _colorBufferCount)
{
	m_screenQuad = std::make_unique<Quad>(nullptr);

	// Create program
	m_program = std::make_unique<ShaderProgram>(_vertShader, _fragShader);

	m_projectionLoc = m_program->GetUniformLocation("in_Projection");
	m_modelLoc = m_program->GetUniformLocation("in_Model");
	
	m_renderTexture = std::make_unique<RenderTexture>(Window::GetScaledWindowSize().x, Window::GetScaledWindowSize().y, _colorBufferCount);
}

void Screen::Draw() const
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Window::GetWindowSize().x), 0.0f, static_cast<float>(Window::GetWindowSize().y), 0.0f, 1.0f);

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(Window::GetWindowSize(), 0) / 2.0f);
	model = glm::scale(model, glm::vec3(Window::GetWindowSize(), 1));

	glUseProgram(m_program->GetId());
	
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_screenQuad->GetVaoId());
	glBindTexture(GL_TEXTURE_2D, m_renderTexture->GetTexture(0));

	glDrawArrays(GL_TRIANGLES, 0, m_screenQuad->GetVertexCount());
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	glUseProgram(0);
}
