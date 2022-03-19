#include "Program.h"

#include <stdexcept>

Program::Program()
{
	m_programId = glCreateProgram();

	m_attributeCount = 0;
}

Program::~Program()
{
	glDeleteProgram(m_programId);
}

void Program::BindAttribute(const std::string& _attribute)
{
	glBindAttribLocation(m_programId, m_attributeCount++, _attribute.c_str());
}

void Program::Link() const
{
	glLinkProgram(m_programId);

	GLint success;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Failed to link GL program!");
	}
}

GLuint Program::GetUniformLocation(const std::string& _uniformName) const
{
	return glGetUniformLocation(m_programId, _uniformName.c_str());
}
