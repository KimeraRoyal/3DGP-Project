#include "Scene.h"

#include <iostream>

#include "Window.h"
#include "Shader.h"

#include "GameObject.h"

size_t Scene::s_lightPosKey = std::hash<std::string>()("in_LightPos");

Scene::Scene(Resources* _resources)
{
	m_resources = _resources;
	
	m_screen = std::make_unique<Screen>(m_resources->GetProgram("data/shaders/screen/screen.vert", "data/shaders/screen/screen.frag"));
}

void Scene::Start()
{
	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update(Time& _time, Input& _input)
{
	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		gameObject->Update(_time, _input);
	}
}

void Scene::Draw()
{
	m_screen->Bind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		gameObject->PreDraw();
	}
	m_screen->Unbind();

	glDisable(GL_DEPTH_TEST);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_FRAMEBUFFER_SRGB);
	m_screen->Draw();
	glDisable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_CULL_FACE);

	glUseProgram(0);
}

std::shared_ptr<GameObject> Scene::CreateGameObject()
{
	std::shared_ptr<GameObject> gameObject = std::shared_ptr<GameObject>(new GameObject);

	gameObject->SetScene(shared_from_this());
	m_gameObjects.push_back(gameObject);
	
	return gameObject;
}