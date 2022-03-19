#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
private:
	GLuint m_shaderId;
	GLuint m_attachedProgramId;
public:
	Shader(int _shaderType, const std::string& _fileName);
	virtual ~Shader();

	Shader(const Shader& _copy) = delete;
	Shader& operator=(const Shader& _other) = delete;

	void Attach(GLuint _programId);
	void Detach(GLuint _programId);
};