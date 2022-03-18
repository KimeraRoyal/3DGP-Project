#include "Program.h"

#include <stdexcept>

Program::Program()
{
	m_programId = glCreateProgram();
}

Program::~Program()
{
	glDeleteProgram(m_programId);
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
