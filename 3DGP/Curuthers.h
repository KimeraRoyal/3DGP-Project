#pragma once

#include <memory>

#include <gl/glew.h>

#include <wavefront/wavefront.h>
#include "RenderTexture.h"

#include "Time.h"

class Curuthers
{
private:
	GLuint m_vertexShaderId;
	GLuint m_fragmentShaderId;

	GLint m_modelLoc;
	GLint m_projectionLoc;

	WfModel m_curuthers;
	std::unique_ptr<RenderTexture> m_renderTexture;

	float m_angle;

	GLuint m_programId;
public:
	Curuthers();
	~Curuthers();

	void Draw(std::unique_ptr<Time>& _time);
};

