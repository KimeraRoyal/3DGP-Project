#include "ShaderProgram.h"

#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>


#include "Shader.h"

ShaderProgram::ShaderProgram()
{
	m_programId = glCreateProgram();

	m_attributeCount = 0;
}

ShaderProgram::ShaderProgram(const std::string& _vertShader, const std::string& _fragShader) : ShaderProgram()
{
	BindAttribute("in_Position");
	BindAttribute("in_Texcoord");
	BindAttribute("in_Normal");

	// Create and compile shaders
	Shader vertexShader = Shader(GL_VERTEX_SHADER, _vertShader);
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, _fragShader);

	// Attach shaders to program
	vertexShader.Attach(GetId());
	fragmentShader.Attach(GetId());

	// Link program
	Link();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_programId);
}

void ShaderProgram::BindAttribute(const std::string& _attribute)
{
	glBindAttribLocation(m_programId, m_attributeCount++, _attribute.c_str());
}

void ShaderProgram::Bind() const
{
	glUseProgram(m_programId);
}

void ShaderProgram::Link() const
{
	glLinkProgram(m_programId);

	GLint success;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success) { throw std::runtime_error("Failed to link GL program!"); }
}

void ShaderProgram::SetUniformValue(const GLuint _uniformLocation, const float& _value) const
{
	glUniform1fv(_uniformLocation, 1, &_value);
}

void ShaderProgram::SetUniformValue(const GLuint _uniformLocation, const glm::vec2& _value) const
{
	glUniform2fv(_uniformLocation, 1, glm::value_ptr(_value));
}

void ShaderProgram::SetUniformValue(const GLuint _uniformLocation, const glm::vec3& _value) const
{
	glUniform3fv(_uniformLocation, 1, glm::value_ptr(_value));
}

void ShaderProgram::SetUniformValue(const GLuint _uniformLocation, const glm::vec4& _value) const
{
	glUniform4fv(_uniformLocation, 1, glm::value_ptr(_value));
}

void ShaderProgram::SetUniformValue(const GLuint _uniformLocation, const glm::mat4& _value) const
{
	glUniformMatrix4fv(_uniformLocation, 1, GL_FALSE, glm::value_ptr(_value));
}

GLuint ShaderProgram::GetUniformLocation(const std::string& _uniformName) const
{
	return glGetUniformLocation(m_programId, _uniformName.c_str());
}

void ShaderProgram::SetUniformValue(const std::string& _uniformName, const float& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformValue(const std::string& _uniformName, const glm::vec2& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformValue(const std::string& _uniformName, const glm::vec3& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformValue(const std::string& _uniformName, const glm::vec4& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformValue(const std::string& _uniformName, const glm::mat4& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}
