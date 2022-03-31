#pragma once

#include <memory>
#include <stack>

#include "ShaderProgram.h"

#include "Time.h"

#include "IModel.h"
#include "GameObject.h"
#include "Screen.h"

class IComponent;

class Scene : public std::enable_shared_from_this<Scene>
{
private:
	std::shared_ptr<ShaderProgram> m_program;

	GLint m_projectionLoc;
	GLint m_viewLoc;

	GLint m_viewPosLoc;
	GLint m_modelMatrixLoc;
	GLint m_lightPosLoc;

	std::vector<GameObject> m_gameObjects;
	std::stack<GameObject> m_inactiveGameObjects;

	std::shared_ptr<IComponent> m_camera;
	std::shared_ptr<IComponent> m_light;
	std::shared_ptr<IComponent> m_model;

	std::shared_ptr<Screen> m_screen;
public:
	Scene();
	~Scene();

	void Start();
	void Update(const std::shared_ptr<Time>& _time);
	void Draw();

	GameObject* CreateGameObject();
	void DestroyGameObject(GameObject* _gameObject);
};

