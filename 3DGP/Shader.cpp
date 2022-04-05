#include "Shader.h"

#include <iostream>
#include <vector>

#include "File.h"

Shader::Shader(const int _shaderType, const std::string& _path)
{
	const std::string sourceText = File::LoadTextFile(File::EvaluatePath(_path));
	const GLchar* source = sourceText.c_str();
	
	// Create and compile shader from source code.
	m_shaderId = glCreateShader(_shaderType);
	glShaderSource(m_shaderId, 1, &source, nullptr);
	glCompileShader(m_shaderId);

	// Check if shader compilation was successful.
	GLint success;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(m_shaderId, maxLength, &maxLength, &errorLog[0]);

		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}

	m_attachedProgramId = 0;
}

Shader::~Shader()
{
	if (m_attachedProgramId) { Detach(m_attachedProgramId); }
	glDeleteShader(m_shaderId);
}

void Shader::Attach(const GLuint _programId)
{
	// Ensure the shader is only attached to one program at a time.
	if (m_attachedProgramId) { Detach(m_attachedProgramId); }
	
	glAttachShader(_programId, m_shaderId);
	m_attachedProgramId = _programId;
}

void Shader::Detach(const GLuint _programId)
{
	glDetachShader(_programId, m_shaderId);
	m_attachedProgramId = 0;
}
