#pragma once

#include <memory>

#include "Texture.h"
#include "VertexArray.h"
#include "Program.h"

#include "Time.h"

#include "IModel.h"
#include "CameraComponent.h"
#include "Light.h"
#include "RenderTexture.h"
#include "Screen.h"

class Scene
{
private:
	std::shared_ptr<Program> m_program;

	GLint m_modelLoc;
	GLint m_projectionLoc;
	GLint m_viewLoc;

	GLint m_viewPosLoc;
	GLint m_lightPosLoc;

	std::unique_ptr<IModel> m_curuthers;

	std::shared_ptr<GameObject> m_cameraObject;
	std::shared_ptr<CameraComponent> m_camera;
	
	Light m_light;
	
	Transform m_curuthersTransform;

	std::shared_ptr<Screen> m_screen;
public:
	Scene();
	~Scene();

	void Update(const std::shared_ptr<Time>& _time);
	void Draw(const std::shared_ptr<Time>& _time);
};

