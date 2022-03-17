#pragma once

#include <GL/glew.h>

class Shader
{
private:
	GLuint m_shaderId;
	GLuint m_attachedProgramId;

	virtual GLuint CreateShader() = 0;
public:
	Shader();
	virtual ~Shader();
	
	void CompileShader(const GLchar* _source);

	void Attach(GLuint _programId);
	void Detach(GLuint _programId);
};