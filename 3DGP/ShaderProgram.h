#pragma once

#include <string>
#include <GL/glew.h>

class ShaderProgram
{
private:
	GLuint m_programId;

	int m_attributeCount;
public:
	ShaderProgram();
	~ShaderProgram();

	ShaderProgram(const ShaderProgram& _copy) = delete;
	ShaderProgram& operator=(const ShaderProgram& _other) = delete;

	void Link() const;

	void BindAttribute(const std::string& _attribute);

	[[nodiscard]] GLuint GetId() const { return m_programId; }
	[[nodiscard]] GLuint GetUniformLocation(const std::string& _uniformName) const;
};

