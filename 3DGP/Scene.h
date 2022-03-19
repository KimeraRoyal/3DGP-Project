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
	std::shared_ptr<Program> m_program2;

	GLint m_modelLoc;
	GLint m_projectionLoc;
	GLint m_viewLoc;

	GLint m_modelLoc2;
	GLint m_projectionLoc2;
	GLint m_viewLoc2;

	WfModel m_curuthers;

	Camera m_camera;
	Transform m_curuthersTransform;
public:
	Scene();
	~Scene();

	void Draw(const std::shared_ptr<Time>& _time);
};

