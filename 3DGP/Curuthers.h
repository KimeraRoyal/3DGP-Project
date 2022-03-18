#pragma once

#include <memory>

#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Program.h"

#include "Time.h"

class Curuthers
{
private:
	std::shared_ptr<Texture> m_texture;

	std::shared_ptr<VertexArray> m_vao;

	std::shared_ptr<Program> m_program;

	GLint m_modelLoc;
	GLint m_projectionLoc;

	float m_angle;
public:
	Curuthers();
	~Curuthers();

	void Draw(std::unique_ptr<Time>& _time);
};

