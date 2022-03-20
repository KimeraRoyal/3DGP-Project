#pragma once

#include <memory>

#include "Texture.h"
#include "VertexArray.h"
#include "Program.h"

#include "Time.h"

#include "IModel.h"
#include "Camera.h"
#include "Light.h"

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

	GLint m_lightPosLoc;

	std::unique_ptr<IModel> m_curuthers;

	Camera m_camera;
	Light m_light;
	
	Transform m_curuthersTransform;
public:
	Scene();
	~Scene();

	void Update(const std::shared_ptr<Time>& _time);
	void Draw(const std::shared_ptr<Time>& _time);
};

