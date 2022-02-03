#pragma once

#include <gl/glew.h>

class Triangle
{
private:

	GLuint m_vaoId;
	
	GLuint m_vertexShaderId;
	GLuint m_fragmentShaderId;

	//TODO: Move into Window
	GLuint m_programId;
public:
	Triangle();
	~Triangle();

	void Draw();
};

