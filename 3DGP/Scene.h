#pragma once

#include <memory>

#include "Texture.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

#include "Time.h"

#include "IModel.h"
#include "Screen.h"
#include "Transform.h"

class GameObject;
class IComponent;

class Scene : public std::enable_shared_from_this<Scene>
{
private:
	std::shared_ptr<ShaderProgram> m_program;

	GLint m_modelLoc;
	GLint m_projectionLoc;
	GLint m_viewLoc;

	GLint m_viewPosLoc;
	GLint m_lightPosLoc;

	std::unique_ptr<IModel> m_curuthers;

	std::vector<std::weak_ptr<GameObject>> m_gameObjects;

	std::shared_ptr<IComponent> m_camera;
	std::shared_ptr<IComponent> m_light;
	std::shared_ptr<IComponent> m_curuthersModel;

	std::shared_ptr<Screen> m_screen;

	std::shared_ptr<GameObject> AccessGameObject(unsigned int _index);
public:
	Scene();
	~Scene();

	void Start();
	void Update(const std::shared_ptr<Time>& _time);
	void Draw();

	std::shared_ptr<GameObject> CreateGameObject();
};

