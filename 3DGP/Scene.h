#pragma once

#include <memory>

#include <wavefront/wavefront.h> 

#include "Texture.h"
#include "VertexArray.h"
#include "Program.h"

#include "Time.h"

#include "Camera.h"

class Scene
{
private:
	std::shared_ptr<Texture> m_texture;

	std::shared_ptr<VertexArray> m_vao;

	std::shared_ptr<Program> m_program;

	GLint m_modelLoc;
	GLint m_projectionLoc;
	GLint m_viewLoc;

	WfModel m_curuthers;

	Camera m_camera;
public:
	Scene();
	~Scene();

	void Draw(const std::weak_ptr<Time>& _time);
};

