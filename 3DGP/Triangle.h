#pragma once

#include <memory>

#include <gl/glew.h>

#include "Time.h"

class Triangle
{
private:

	GLuint m_vaoId;
	
	GLuint m_vertexShaderId;
	GLuint m_fragmentShaderId;

	GLuint m_textureId;

	GLint m_modelLoc;
	GLint m_projectionLoc;

	float m_angle;

	//TODO: Move into Window
	GLuint m_programId;
public:
	Triangle();
	~Triangle();

	void Draw(std::unique_ptr<Time>& _time);
};

