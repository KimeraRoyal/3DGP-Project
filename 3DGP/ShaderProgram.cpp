#include "ShaderProgram.h"

#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

ShaderProgram::ShaderProgram()
{
	m_programId = glCreateProgram();

	m_attributeCount = 0;

	BindAttribute("in_Position");
	BindAttribute("in_Texcoord");
	BindAttribute("in_Normal");
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_programId);
}

void ShaderProgram::Load(const std::string& _path, Resources* _resources)
{
	Load(_path + ".vert", _path + ".frag");
}

void ShaderProgram::Load(const std::string& _vertShader, const std::string& _fragShader)
{
	// Create and compile shaders
	Shader vertexShader = Shader(GL_VERTEX_SHADER, _vertShader);
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, _fragShader);

	// Attach shaders to program
	vertexShader.Attach(GetId());
	fragmentShader.Attach(GetId());

	// Link program
	Link();

	SetUniformKeys();
}

void ShaderProgram::Link() const
{
	glLinkProgram(m_programId);

	GLint success;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success) { throw std::runtime_error("Failed to link GL program!"); }
}

void ShaderProgram::BindAttribute(const std::string& _attribute)
{
	glBindAttribLocation(m_programId, m_attributeCount++, _attribute.c_str());
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

void ShaderProgram::SetUniformValueByKey(const size_t _uniformKey, const float& _value) const
{
	if (m_uniformLocations.find(_uniformKey) == m_uniformLocations.end()) { return; }
	SetUniformValue(m_uniformLocations.at(_uniformKey), _value);
}

void ShaderProgram::SetUniformValueByKey(const size_t _uniformKey, const glm::vec2& _value) const
{
	if (m_uniformLocations.find(_uniformKey) == m_uniformLocations.end()) { return; }
	SetUniformValue(m_uniformLocations.at(_uniformKey), _value);
}

void ShaderProgram::SetUniformValueByKey(const size_t _uniformKey, const glm::vec3& _value) const
{
	if (m_uniformLocations.find(_uniformKey) == m_uniformLocations.end()) { return; }
	SetUniformValue(m_uniformLocations.at(_uniformKey), _value);
}

void ShaderProgram::SetUniformValueByKey(const size_t _uniformKey, const glm::vec4& _value) const
{
	if (m_uniformLocations.find(_uniformKey) == m_uniformLocations.end()) { return; }
	SetUniformValue(m_uniformLocations.at(_uniformKey), _value);
}

void ShaderProgram::SetUniformValueByKey(const size_t _uniformKey, const glm::mat4& _value) const
{
	if (m_uniformLocations.find(_uniformKey) == m_uniformLocations.end()) { return; }
	SetUniformValue(m_uniformLocations.at(_uniformKey), _value);
}

GLuint ShaderProgram::GetUniformLocation(const std::string& _uniformName) const
{
	return glGetUniformLocation(m_programId, _uniformName.c_str());
}

void ShaderProgram::SetUniformValueByName(const std::string& _uniformName, const float& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformValueByName(const std::string& _uniformName, const glm::vec2& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformValueByName(const std::string& _uniformName, const glm::vec3& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformValueByName(const std::string& _uniformName, const glm::vec4& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformValueByName(const std::string& _uniformName, const glm::mat4& _value) const
{
	SetUniformValue(GetUniformLocation(_uniformName), _value);
}

void ShaderProgram::SetUniformKeys()
{
	GLint activeUniforms = 0;
	glGetProgramInterfaceiv(m_programId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &activeUniforms);
	
	std::vector<GLchar> nameData(256);
	GLenum uniformProperties[] = { GL_NAME_LENGTH };
	GLint uniformValues[] = { 0 };

	std::vector<std::string> uniformNames;

#ifdef _DEBUG
	std::printf("Hashing uniforms: ");
#endif
	for(GLint uniformLocation = 0; uniformLocation < activeUniforms; ++uniformLocation)
	{
#ifdef _DEBUG
		if (uniformLocation > 0) { std::printf(","); }
#endif
		glGetProgramResourceiv(m_programId, GL_UNIFORM, uniformLocation, 1, &uniformProperties[0], 1, nullptr, &uniformValues[0]);

		nameData.resize(uniformValues[0]);
		glGetProgramResourceName(m_programId, GL_UNIFORM, uniformLocation, nameData.size(), nullptr, &nameData[0]);
		uniformNames.emplace_back();

		std::string uniformName = std::string(static_cast<char*>(&nameData[0]), nameData.size() - 1);
		
		const size_t key = std::hash<std::string>()(uniformName);
		m_uniformLocations.insert(std::make_pair(key, uniformLocation));

#ifdef _DEBUG
		std::printf(" %d: \"%s\" (%u)", uniformLocation, uniformName.c_str(), key);
#endif
	}
#ifdef _DEBUG
	std::printf("\n");
#endif
}