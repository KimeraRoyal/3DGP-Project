#include "ShaderProgram.h"

#include <stdexcept>

#include "Shader.h"

ShaderProgram::ShaderProgram()
{
	m_programId = glCreateProgram();

	m_attributeCount = 0;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_programId);
}

void ShaderProgram::BindAttribute(const std::string& _attribute)
{
	glBindAttribLocation(m_programId, m_attributeCount++, _attribute.c_str());
}

void ShaderProgram::Link() const
{
	glLinkProgram(m_programId);

	GLint success;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success) { throw std::runtime_error("Failed to link GL program!"); }
}

GLuint ShaderProgram::GetUniformLocation(const std::string& _uniformName) const
{
	return glGetUniformLocation(m_programId, _uniformName.c_str());
}
